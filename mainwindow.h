#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "SettingsWindow/settingswindow.h"
#include "VehicleWizard/vehiclewizard.h"
#include <QAction>
#include <QSettings>
#include <QStringList>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
signals:
    void updateVehiclesMenu();

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void updateVehiclesList();

private:
    SettingsWindow settingsWindow;
    VehicleWizard wizard;

    QSettings *settings;
    QString settingsFile;
    QStringList vehiclesListString;
    void checkFile(QString filename);


private slots:
    // TODO: УБРАТЬ ЭТО
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
