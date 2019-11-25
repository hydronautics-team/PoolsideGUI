#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    connect(action_enable_AUV, SIGNAL(triggered()),this, SLOT(enableAUVMode()));
    connect(action_enable_ROV, SIGNAL(triggered()),this, SLOT(enableROVMode()));
    connect(action_config_thrusters, SIGNAL(triggered()),this, SLOT(showPageConfigThruster()));
}


void MainWindow::enableAUVMode()
{
    stackedWidget->setCurrentWidget(pageAUVMode);
}

void MainWindow::enableROVMode()
{
    stackedWidget->setCurrentWidget(pageROVMode);
}

void MainWindow::showPageConfigThruster()
{
    settingsWindow.show();
    settingsWindow.showPageConfigThruster();
}
