#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QSettings>
#include <QStringList>

#include "ui_mainwindow.h"
#include "SettingsWindow/settingswindow.h"
#include "VehicleWizard/vehiclewizard.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void updateVehiclesMenu();
    void updateVehicleConfigurationMenu();

private:
    SettingsWindow settingsWindow;
    VehicleWizard wizard;

    QString settingsFile;
    QSettings *settings;

    QString currentVehicle;
    QString currentConfiguration;

    void checkFile(QString filename);
    void enableAUVMode();
    void enableROVMode();

private slots:
    // menu actions
    void createVehicle();
    void chooseVehicle(QAction *action);
    void chooseConfiguration(QAction *action);
};

#endif // MAINWINDOW_H
