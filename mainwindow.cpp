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
    QMainWindow::showFullScreen();
    QMainWindow::menuBar()->setVisible(false);


    // update vehicle and all parameters
    connect(&wizard, SIGNAL(updateMainWindow()), this, SIGNAL(updateVehicle()));
    connect(this, SIGNAL(updateVehicle()), this, SLOT(updateVehiclesMenu()));
    connect(this, SIGNAL(updateVehicle()), &settingsWindow, SIGNAL(updateVehicle()));
    connect(this, SIGNAL(updateVehicle()), this, SLOT(updateVehicleUi()));

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

    connect(serial_client, SIGNAL(dataUpdated()), this, SLOT(updateDataUi()));
    connect(settingsWindow.pageConfigThruster, SIGNAL(ThrusterChanged(unsigned int)), serial_client, SLOT(changeSelectedThruster(unsigned int)));


    UDP_Client *udp_client = new UDP_Client();
    udp_client->start();

    connect(udp_client, SIGNAL(dataUpdated()), this, SLOT(updateDataUi()));
    connect(udp_client, SIGNAL(dataUpdated()), settingsWindow.pageVehicleSettings, SLOT(updateData()));

    connect(this, SIGNAL(updateCompass(double)), compassFrame, SLOT(setYaw(double)));
    connect(checkBoxStabilizeRoll, SIGNAL(stateChanged(int)), this, SLOT(checkboxChecked(int)));
    connect(pushButtonResetIMU, SIGNAL(pressed()), this, SLOT(resetImu()));
    connect(pushButtonResetIMU, SIGNAL(released()), this, SLOT(clearResetImu()));

    //load image
    vehiclePic->setScene(new QGraphicsScene(vehiclePic));
    vehiclePic->setStyleSheet("background: transparent");
    vehiclePic->setRenderHint(QPainter::Antialiasing);
    vehiclePic->scene()->addPixmap(QPixmap(":/images/Cousteau_2A.png"))->setTransform(QTransform::fromScale(0.2, 0.2));

    initializeDataUi();
    updateDataUi();

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
    qDebug() << currentConfiguration;
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

//void MainWindow::enableAUVMode()
//{
//    stackedWidget->setCurrentWidget(pageAUVMode);
//}

//void MainWindow::enableROVMode()
//{
//    stackedWidget->setCurrentWidget(pageROVMode);
//}

void MainWindow::updateVehicleUi()
{
    currentVehicle = settings->value("currentVehicle").toString();
    thrustersCount = settings->value("vehicle/" + currentVehicle + "/thrusters/count").toInt();
    //update bars
    foreach (QProgressBar *bar, thrusterBarGroup) {
        bar->hide();
    }
    for (int i = 0; i < thrustersCount; i++){
        thrusterBarGroup[i]->show();
        thrusterBarGroup[i]->setFormat(settings->value("vehicle/" + currentVehicle + "/thrusters/" + QString::number(i) + "/name").toString());
    }
    initializeDataUi();
    updateDataUi();
}

void MainWindow::initializeDataUi()
{
    foreach (QProgressBar *bar, thrusterBarGroup) {
        bar->setValue(0);
    }
    pitchBar->setValue(0);
    depthBar->setValue(0);
    depthLabel->setText("0");   // label under bar
    pitchLabel->setText("0");   // label under bar
    sensorsDepthLabel->setText("0");
    sensorsPitchLabel->setText("0");
    sensorsYawLabel->setText("0");
    sensorsRollLabel->setText("0");
    emit updateCompass(0);
}

void MainWindow::updateDataUi()
{
    // Get data from UVState object
    ImuData sensors = uv_interface.getImuData();

    // Update user interface
    depthBar->setValue(static_cast<int>(sensors.depth*depthLin + depthOffset));   // bar
    pitchBar->setValue(static_cast<int>(sensors.pitch));   // bar

    depthLabel->setText(QString::number(sensors.depth *depthLin + depthOffset , 'f', 2));   // label under bar
    pitchLabel->setText(QString::number(sensors.pitch, 'f', 2));   // label under bar

    sensorsDepthLabel->setText(QString::number(sensors.depth*depthLin + depthOffset, 'f', 2));
    sensorsPitchLabel->setText(QString::number(sensors.pitch, 'f', 2));

    sensorsYawLabel->setText(QString::number(sensors.yaw, 'f', 2));
    sensorsRollLabel->setText(QString::number(sensors.roll, 'f', 2));

    // Update drawing of a compass
    emit updateCompass(sensors.yaw);

    ControlData control = uv_interface.getControlData();

    label_march->setText(QString::number(control.march, 'f', 2));
    label_lag->setText(QString::number(control.lag, 'f', 2));
    label_depth->setText(QString::number(control.depth, 'f', 2));
    label_yaw->setText(QString::number(control.yaw, 'f', 2));
    label_roll->setText(QString::number(control.roll, 'f', 2));

    label_grabber->setText(QString::number(uv_interface.getDeviceVelocity(UV_Device::DEVICE_GRAB), 'f', 2));
    label_grabber_rotation->setText(QString::number(uv_interface.getDeviceVelocity(UV_Device::DEVICE_GRAB_ROTATE), 'f', 2));
    label_tilt->setText(QString::number(uv_interface.getDeviceVelocity(UV_Device::DEVICE_TILT), 'f', 2));
//    qDebug() << "updateData";
}

// TODO это больше не нужно
void MainWindow::checkboxChecked(int i)
{
//    UV_State *state;
//    IBasicData interface(&UVState, &UVMutex);
//    state = interface.gainAccess();
//    if(state->messageType == 0) {
//        state->messageType = 2;
//    }
//    else {
//        state->messageType = 0;
//    }
//    interface.closeAccess();
}

void MainWindow::resetImu()
{
    IUserInterfaceData interface;
    interface.setResetImuValue(true);
}

void MainWindow::clearResetImu()
{
    IUserInterfaceData interface;
    interface.setResetImuValue(false);
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
