#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "ui_settingswindow.h"

class SettingsWindow : public QWidget, private Ui::SettingsWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);

public slots:
    void showPageConfigThruster();
    void showPageConfigRS();
    void showPageConfigSSH();
    void showPageConfigCoef();
    void showPageConfigControls();
    void showPageConfigView();
    void showPageAboutProgram();
    void showPageOtherSettings();

private:
    //Serial serial;
    //Messages messages;

};

#endif // SETTINGSWINDOW_H
