#include "mainwindow.h"
#include <QDebug>
#include <QFileInfo>

#include "ui_settingswindow.h"

#include "serial_client.h"
#include "udp_client.h"

#include <QShortcut>
#include <QApplication>
#include <QThread>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    setupUi(this);
    //start in full screen format
//    QMainWindow::showFullScreen();
//    QMainWindow::menuBar()->setVisible(false);


    // update vehicle and all parameters
    connect(&wizard, SIGNAL(updateMainWindow()), this, SIGNAL(updateVehicle()));
    connect(this, SIGNAL(updateVehicle()), this, SLOT(updateVehiclesMenu()));
    connect(this, SIGNAL(updateVehicle()), &settingsWindow, SIGNAL(updateVehicle()));
    connect(this, SIGNAL(updateVehicle()), pageROVMode, SLOT(updateVehicle()));

    // Reading the key combination of turning the window to the full screen and back
    QShortcut *keyCtrlF = new QShortcut(this);
    keyCtrlF->setKey(Qt::CTRL+Qt::Key_F);
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::noFullScreenKey);

    // Controller Changed
    controller = new Mouse3d("3dMouse", 5);
    connect(&settingsWindow, SIGNAL(controllerChanged(unsigned int, QString)), this, SLOT(changeController(unsigned int, QString)));

    // Menu:
    // Vehicle
    // New vehicle
    connect(action_create_vehicle, SIGNAL(triggered()), this, SLOT(createVehicle()));
    // Choose vehicle and configuration
    connect(menu_choose_configuration,SIGNAL(triggered(QAction*)), this, SLOT(chooseConfiguration(QAction*)));
    connect(menu_choose_vehicle, SIGNAL(triggered(QAction*)), this, SLOT(chooseVehicle(QAction*)));
    // Settings
    connect(action_config_com, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigRS()));
    connect(action_config_thrusters, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigThruster()));
    connect(action_config_coef, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigCoef()));
    // Surface control unit
    connect(action_config_controls, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigControls()));
    connect(action_config_view, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigView()));
    // Other settings
    connect(action_about_program, SIGNAL(triggered()), &settingsWindow, SLOT(showPageAboutProgram()));
    connect(action_other_settings, SIGNAL(triggered()), &settingsWindow, SLOT(showPageOtherSettings()));
    connect(action_full_screen, &QAction::triggered, this, &MainWindow::fullScreen);

    settingsFile = QApplication::applicationDirPath() + "/settings.ini"; // path to settings file
    checkFile(settingsFile); // check file existance
    settings = new QSettings(settingsFile, QSettings::IniFormat);

    currentVehicle = settings->value("currentVehicle").toString();
    currentConfiguration = settings->value("currentConfiguration").toString();
    emit updateVehicle();


    Serial_Client *serial_client = new Serial_Client();
    serial_client->start();

    connect(serial_client, SIGNAL(dataUpdated()), pageROVMode, SLOT(updateData()));
    connect(settingsWindow.pageConfigThruster, SIGNAL(ThrusterChanged(unsigned int)), serial_client, SLOT(changeSelectedThruster(unsigned int)));

    UDP_Client *udp_client = new UDP_Client();
    udp_client->start();

    connect(udp_client, SIGNAL(dataUpdated()), pageROVMode, SLOT(updateData()));
    connect(udp_client, SIGNAL(dataUpdated()), settingsWindow.pageVehicleSettings, SLOT(updateData()));

//    connect(pushButtonReconnectROV, SIGNAL(pressed()), this, SLOT(reconnectROV()));

}

void MainWindow::reconnectROV()
{
//    if  (serial_client != nullptr){
//        delete serial_client;
//        qDebug() << "delete serial_client in reconnectROV";
//    }
    qDebug() << "reconnectROV";

    Serial_Client *serial_client = new Serial_Client();
    serial_client->start();

    connect(serial_client, SIGNAL(dataUpdated()), pageROVMode, SLOT(updateData()));
    connect(settingsWindow.pageConfigThruster, SIGNAL(ThrusterChanged(unsigned int)), serial_client, SLOT(changeSelectedThruster(unsigned int)));

    UDP_Client *udp_client = new UDP_Client();
    udp_client->start();

    connect(udp_client, SIGNAL(dataUpdated()), pageROVMode, SLOT(updateData()));
    connect(udp_client, SIGNAL(dataUpdated()), settingsWindow.pageVehicleSettings, SLOT(updateData()));
}

void MainWindow::createVehicle()
{
    wizard.startStateMachine();
    wizard.show();
}

void MainWindow::chooseVehicle(QAction *action)
{
    currentVehicle = action->text();
    settings->beginGroup("vehicle/" + currentVehicle + "/configuration");
    foreach (QString name, settings->childKeys()) {
        if (settings->value(name).toBool()){
            currentConfiguration = name;
            break;
        }
    }
    settings->endGroup();

    settings->setValue("currentVehicle", currentVehicle);
    settings->setValue("currentConfiguration", currentConfiguration);
    emit updateVehicle();
}

void MainWindow::chooseConfiguration(QAction *action)
{
    currentConfiguration = action->text();
    settings->setValue("currentConfiguration", currentConfiguration);
    updateVehicleConfigurationMenu();
}

void MainWindow::fullScreen()
{
    QMainWindow::showFullScreen();
    QMainWindow::menuBar()->setVisible(false);
}

void MainWindow::noFullScreenKey()
{
    if(QMainWindow::windowState() == Qt::WindowFullScreen){
        QMainWindow::showNormal();
        QMainWindow::menuBar()->setVisible(true);
    }
}

void MainWindow::updateVehiclesMenu()
{
    if (!currentVehicle.isEmpty()){
        if (!menu_choose_vehicle->isEmpty())
            menu_choose_vehicle->clear();
        settings->beginGroup("vehicle");
        foreach (QString name, settings->childGroups()) {
            QAction *vehicle = new QAction(name);
            if (name == currentVehicle){
                QFont f = vehicle->font();
                f.setBold(true);
                vehicle->setFont(f);
                menu_choose_vehicle->addAction(vehicle);
            }
            else
                menu_choose_vehicle->addAction(vehicle);
        }
        settings->endGroup();
    }
    settings->sync();
    qDebug () << currentVehicle;
    updateVehicleConfigurationMenu();
}

void MainWindow::updateVehicleConfigurationMenu()
{
    menu_choose_configuration->clear();
    settings->beginGroup("vehicle/" + currentVehicle + "/configuration");
    foreach (QString name, settings->childKeys()) {
        if (settings->value(name).toBool()){
            QAction *configuration = new QAction(name);
            if (name == currentConfiguration){
                QFont f = configuration->font();
                f.setBold(true);
                configuration->setFont(f);
                menu_choose_configuration->addAction(configuration);
            }
            else
                menu_choose_configuration->addAction(configuration);
        }
    }
    settings->endGroup();
    qDebug () << currentConfiguration;
}

void MainWindow::checkFile(QString filename)
{
    QFile file(filename);
    if(QFileInfo::exists(filename))
    {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.close();
    }
    else
    {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.close();
    }
}

void MainWindow::enableAUVMode()
{
    stackedWidget->setCurrentWidget(pageAUVMode);
}

void MainWindow::enableROVMode()
{
    stackedWidget->setCurrentWidget(pageROVMode);
}

void MainWindow::changeController(unsigned int current_device, QString name)
{
    if(controller != nullptr) {
        delete controller;
        qDebug() << "delete controller";
    }
    switch (current_device) {
    case 0:
        qDebug() << "no Keyboard -> 3Dmouse connected";
        controller = new Mouse3d("3dMouse", 5);
        break;
    case 1:
        controller = new Mouse3d("3dMouse", 5);
        break;
    case 2:
        controller = new Joystick(name, 10, 0); //default id = 0;
        break;
    }
}

void MainWindow::on_pushButtonReconnectROV_clicked()
{
    emit reconnectROV();
}

