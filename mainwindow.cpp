#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    // menu AUV/ROV
    connect(action_enable_AUV, SIGNAL(triggered()),this, SLOT(enableAUVMode()));
    connect(action_enable_ROV, SIGNAL(triggered()),this, SLOT(enableROVMode()));
    // menu Vehicle
    connect(action_config_com, SIGNAL(triggered()),this, SLOT(showPageConfigCommunication()));
    connect(action_config_thrusters, SIGNAL(triggered()),this, SLOT(showPageConfigThruster()));
    connect(action_config_coef, SIGNAL(triggered()),this, SLOT(showPageConfigCoef()));
    // menu Surface control unit
    connect(action_config_controls, SIGNAL(triggered()),this, SLOT(showPageConfigControls()));
    connect(action_config_view, SIGNAL(triggered()),this, SLOT(showPageConfigView()));
    // menu Other
    connect(action_about_program, SIGNAL(triggered()),this, SLOT(showPageAboutProgram()));
    connect(action_other_settings, SIGNAL(triggered()),this, SLOT(showPageOtherSettings()));
}

void MainWindow::enableAUVMode()
{
    stackedWidget->setCurrentWidget(pageAUVMode);
}

void MainWindow::enableROVMode()
{
    stackedWidget->setCurrentWidget(pageROVMode);
}

void MainWindow::showPageConfigCommunication()
{
    settingsWindow.show();
    settingsWindow.showPageConfigCommunication();
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
