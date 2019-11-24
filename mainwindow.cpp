#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    connect(action_enable_AUV, SIGNAL(triggered()),this, SLOT(enableAUVMode()));
    connect(action_enable_ROV, SIGNAL(triggered()),this, SLOT(enableROVMode()));
}

void MainWindow::enableAUVMode()
{
    stackedWidget->setCurrentWidget(pageAUVMode);
}

void MainWindow::enableROVMode()
{
    stackedWidget->setCurrentWidget(pageROVMode);
}
