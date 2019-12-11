#include "mainwindow.h"
#include <QDebug>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    // Menu actions:
    // Vehicle
    //      New vehicle
    connect(action_create_vehicle, SIGNAL(triggered()), this, SLOT(createVehicle()));
    //      Configuration
    connect(action_enable_AUV, SIGNAL(triggered()), this, SLOT(enableAUVMode()));
    connect(action_enable_ROV, SIGNAL(triggered()), this, SLOT(enableROVMode()));

    connect(action_config_RS, SIGNAL(triggered()), this, SLOT(showPageConfigRS()));
    connect(action_config_SSH, SIGNAL(triggered()), this, SLOT(showPageConfigSSH()));
    connect(action_config_thrusters, SIGNAL(triggered()), this, SLOT(showPageConfigThruster()));
    connect(action_config_coef, SIGNAL(triggered()), this, SLOT(showPageConfigCoef()));

    // Surface control unit
    connect(action_config_controls, SIGNAL(triggered()), this, SLOT(showPageConfigControls()));
    connect(action_config_view, SIGNAL(triggered()), this, SLOT(showPageConfigView()));

    // Other
    connect(action_about_program, SIGNAL(triggered()), this, SLOT(showPageAboutProgram()));
    connect(action_other_settings, SIGNAL(triggered()), this, SLOT(showPageOtherSettings()));

    connect(&wizard, SIGNAL(updateVehiclesMenu()), this, SLOT(updateVehiclesList()));
    connect(this, SIGNAL(updateVehiclesMenu()), this, SLOT(updateVehiclesList()));

    settingsFile = QApplication::applicationDirPath() + "/settings.ini";
    settings = new QSettings(settingsFile, QSettings::IniFormat);
    checkFile(settingsFile);

    emit updateVehiclesMenu();
}

void MainWindow::createVehicle()
{
    wizard.startStateMachine();
    wizard.show();
}

void MainWindow::chooseVehicle()
{

}

void MainWindow::enableAUVMode()
{
    stackedWidget->setCurrentWidget(pageAUVMode);
}

void MainWindow::enableROVMode()
{
    stackedWidget->setCurrentWidget(pageROVMode);
}

void MainWindow::showPageConfigRS()
{
    settingsWindow.show();
    settingsWindow.showPageConfigRS();
}

void MainWindow::showPageConfigSSH()
{
    settingsWindow.show();
    settingsWindow.showPageConfigSSH();
}

void MainWindow::showPageConfigThruster()
{
    settingsWindow.show();
    settingsWindow.showPageConfigThruster();
}

void MainWindow::showPageConfigCoef()
{
    settingsWindow.show();
    settingsWindow.showPageConfigCoef();
}

void MainWindow::showPageConfigControls()
{
    settingsWindow.show();
    settingsWindow.showPageConfigControls();
}

void MainWindow::showPageConfigView()
{
    settingsWindow.show();
    settingsWindow.showPageConfigView();
}

void MainWindow::showPageAboutProgram()
{
    settingsWindow.show();
    settingsWindow.showPageAboutProgram();
}

void MainWindow::showPageOtherSettings()
{
    settingsWindow.show();
    settingsWindow.showPageOtherSettings();
}

void MainWindow::updateVehiclesList()
{
    if (!menuChooseVehicle->isEmpty())
        menuChooseVehicle->clear();
    settings->beginGroup("vehicle");
    vehiclesListString = settings->childGroups();
    settings->endGroup();
    qDebug () << vehiclesListString;
    foreach (QString name, vehiclesListString) {
        QAction *vehicle = new QAction(name);
        menuChooseVehicle->addAction(vehicle);
        qDebug () << name;
    }
}

void MainWindow::checkFile(QString filename)
{
    QFile file(filename);
    if(QFileInfo::exists(filename))
    {
        qDebug () << "file exists";
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        qDebug()<<"file already created";
        file.close();
    }
    else
    {
        qDebug () << "file does not exists";
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        qDebug()<<"file created"<<endl;
        file.close();
    }
}
