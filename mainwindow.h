#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QSettings>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

#include "ui_mainwindow.h"

#include "UV/iuserinterfacedata.h"
#include "SettingsWindow/settingswindow.h"
#include "VehicleWizard/vehiclewizard.h"
#include "ControlSettings/Joystick.h"
#include "ControlSettings/Keyboard.h"
#include "ControlSettings/Mouse3d.h"
#include "serial_client.h"
#include "udp_client.h"

class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
signals:
    void updateVehicle();
    //import from old interface
    void updateCompass(double yaw);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    //import from old interface
    float depthLin = 9.9546;
    float depthOffset = 0;

public slots:
    void changeController(unsigned int current_device, QString name);
    void reconnectROV();

private slots:
    void updateVehiclesMenu();

    //import from old interface
    void updateVehicleUi();
    void updateUi();

    void resetImu();
    void clearResetImu();

private:
    SettingsWindow settingsWindow;
    VehicleWizard wizard;
    QString settingsFile;
    QSettings *settings;
    QString currentVehicle;
    QString currentConfiguration;

    void updateVehicleConfigurationMenu();
    void checkFile(QString filename);
//    void enableAUVMode();
//    void enableROVMode();
    ControlBase *controller;
    Serial_Client *serial_client;
    UDP_Client *udp_client;

    //import from old interface
    void initializeDataUi();
    int thrustersCount;
    QList<QProgressBar *> thrusterBarGroup;
    QGraphicsScene *scene;
    //QGraphicsPixmapItem *picROV;
    //QGraphicsTextItem *txtCurrentYaw;

    // Interface for accessing UVState object
    IUserInterfaceData uv_interface;

private slots:
    // menu actions
    void createVehicle();
    void chooseVehicle(QAction *action);
    void chooseConfiguration(QAction *action);
    // full screen key combination
    void fullScreenKey();

    void reconnectcROVclick();

};

#endif // MAINWINDOW_H
