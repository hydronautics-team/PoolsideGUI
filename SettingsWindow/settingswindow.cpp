#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(this, SIGNAL(updateVehicle()), &thrusterSettings, SIGNAL(updateVehicle()));
}

void SettingsWindow::showPageConfigThruster()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigThruster);
}

void SettingsWindow::showPageConfigRS()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigRS);
}

void SettingsWindow::showPageConfigSSH()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigSSH);
}

void SettingsWindow::showPageConfigCoef()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigCoef);
}

void SettingsWindow::showPageConfigControls()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigControls);
}

void SettingsWindow::showPageConfigView()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigView);
}

void SettingsWindow::showPageAboutProgram()
{
    this->show();
    stackedWidget->setCurrentWidget(pageAboutProgram);
}

void SettingsWindow::showPageOtherSettings()
{
    this->show();
    stackedWidget->setCurrentWidget(pageOtherSettings);
}
