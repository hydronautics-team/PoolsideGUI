#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QSettings>

#include "ui_mainwindow.h"

#include "rovmodewidget.h"
#include "SettingsWindow/settingswindow.h"
#include "VehicleWizard/vehiclewizard.h"
#include "Drivers/joystick.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
signals:
    void updateVehicle();

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void changeController(unsigned int id, QString name);

private slots:
    void updateVehiclesMenu();

private:
    SettingsWindow settingsWindow;
    VehicleWizard wizard;
    QString settingsFile;
    QSettings *settings;
    QString currentVehicle;
    QString currentConfiguration;

    void updateVehicleConfigurationMenu();
    void checkFile(QString filename);
    void enableAUVMode();
    void enableROVMode();

    ControlBase *controller;

private slots:
    // menu actions
    void createVehicle();
    void chooseVehicle(QAction *action);
    void chooseConfiguration(QAction *action);
};

#endif // MAINWINDOW_H
