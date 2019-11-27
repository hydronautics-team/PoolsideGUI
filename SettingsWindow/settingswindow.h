#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "ui_settingswindow.h"

class SettingsWindow : public QWidget, private Ui::SettingsWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    void showPageConfigThruster();
    void showPageConfigCommunication();
    void showPageConfigCoef();
    void showPageConfigControls();
    void showPageConfigView();
    void showPageAboutProgram();
    void showPageOtherSettings();
};

#endif // SETTINGSWINDOW_H
