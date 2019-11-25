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
