#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

void SettingsWindow::showPageConfigThruster()
{
    stackedWidget->setCurrentWidget(pageConfigThruster);
}

void SettingsWindow::showPageConfigCommunication()
{
    stackedWidget->setCurrentWidget(pageConfigCommunication);
}

void SettingsWindow::showPageConfigCoef()
{
    stackedWidget->setCurrentWidget(pageConfigCoef);
}

void SettingsWindow::showPageConfigControls()
{
    stackedWidget->setCurrentWidget(pageConfigControls);
}

void SettingsWindow::showPageConfigView()
{
    stackedWidget->setCurrentWidget(pageConfigView);
}

void SettingsWindow::showPageAboutProgram()
{
    stackedWidget->setCurrentWidget(pageAboutProgram);
}

void SettingsWindow::showPageOtherSettings()
{
    stackedWidget->setCurrentWidget(pageOtherSettings);
}
