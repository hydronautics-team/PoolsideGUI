#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    // Menu actions:
    // Vehicle
    //      New vehicle
    connect(action_create_vehicle, SIGNAL(triggered()),this, SLOT(createVehicle()));
    //      Choose vehicle
    connect(action_choose_vehicle, SIGNAL(triggered()),this, SLOT(chooseVehicle()));
    //      Configuration
    connect(action_enable_AUV, SIGNAL(triggered()),this, SLOT(enableAUVMode()));
    connect(action_enable_ROV, SIGNAL(triggered()),this, SLOT(enableROVMode()));

    connect(action_config_RS, SIGNAL(triggered()),this, SLOT(showPageConfigRS()));
    connect(action_config_SSH, SIGNAL(triggered()),this, SLOT(showPageConfigSSH()));
    connect(action_config_thrusters, SIGNAL(triggered()),this, SLOT(showPageConfigThruster()));
    connect(action_config_coef, SIGNAL(triggered()),this, SLOT(showPageConfigCoef()));

    // Surface control unit
    connect(action_config_controls, SIGNAL(triggered()),this, SLOT(showPageConfigControls()));
    connect(action_config_view, SIGNAL(triggered()),this, SLOT(showPageConfigView()));

    // Other
    connect(action_about_program, SIGNAL(triggered()),this, SLOT(showPageAboutProgram()));
    connect(action_other_settings, SIGNAL(triggered()),this, SLOT(showPageOtherSettings()));
}

void MainWindow::createVehicle()
{
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
