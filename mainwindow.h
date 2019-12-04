#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "SettingsWindow/settingswindow.h"
#include "CreateVehicleWizard/createvehiclewizard.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    SettingsWindow settingsWindow;
    CreateVehicleWizard wizard;

private slots:
    // Menu actions:
    // Vehicle:
    //      New vehicle
    void createVehicle();
    //      Choose vehicle
    void chooseVehicle();
    //      Configuration
    void enableAUVMode();
    void enableROVMode();
    //      Settings
    void showPageConfigThruster();
    void showPageConfigRS();
    void showPageConfigSSH();
    void showPageConfigCoef();
    // Surface control unit:
    void showPageConfigControls();
    void showPageConfigView();
    // Other:
    void showPageAboutProgram();
    void showPageOtherSettings();
};

#endif // MAINWINDOW_H
