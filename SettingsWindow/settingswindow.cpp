#include "settingswindow.h"
#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    qDebug () << " - SettingsWindow constructor";
    connect(this, SIGNAL(updateVehicle()),
            pageConfigThruster, SLOT(updateVehicle()));
}

void SettingsWindow::showPageConfigThruster()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigThruster);
    this->setWindowTitle("Thruster settings");
}

void SettingsWindow::showPageConfigRS()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigRS);
    this->setWindowTitle("Communication settings");
}

void SettingsWindow::showPageConfigSSH()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigSSH);
    this->setWindowTitle("Communication settings");
}

void SettingsWindow::showPageConfigCoef()
{
    this->show();
    stackedWidget->setCurrentWidget(pageVehicleSettings);
    this->setWindowTitle("Vehicle settings");
}

void SettingsWindow::showPageConfigControls()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigControls);
    this->setWindowTitle("Controls settings");
}

void SettingsWindow::showPageConfigView()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigView);
    this->setWindowTitle("View settings");
}

void SettingsWindow::showPageAboutProgram()
{
    this->show();
    stackedWidget->setCurrentWidget(pageAboutProgram);
    this->setWindowTitle("About program");
}

void SettingsWindow::showPageOtherSettings()
{
    this->show();
    stackedWidget->setCurrentWidget(pageOtherSettings);
    this->setWindowTitle("Other settings");
}
