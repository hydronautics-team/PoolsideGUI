#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QSettings>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileInfo>
#include <QDebug>
#include <QShortcut>
#include <QApplication>
#include <QThread>
#include <QTimer>

#include "KX_Pult/kx_protocol.h"
#include "KX_Pult/qkx_coeffs.h"

#include "ui_mainwindow.h"

#include "UV/iuserinterfacedata.h"
#include "VehicleWizard/vehiclewizard.h"
#include "CommunicationSettings/SerialClient.h"
#include "CommunicationSettings/UdpClient.h"
//#include "ControlSettings/ControlWindow.h"
//#include "ControlSettings/Control.h"
#include "ControlSettings/Joystick.h"
#include "ControlSettings/Keyboard.h"
#include "ThrusterSettings/ThrusterWindow.h"
#include "StabilizationSettings/StabilizationWindow.h"

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
    Joystick *controller = nullptr;

public slots:
    void reconnectROV();
//    void enableControllerChanged(Control::e_controllerType controllerType, bool enabel);

private:
    QTimer *updateControl_timer;

    StabilizationWindow stabilizationWindow;
//    ControlWindow controlWindow;
    ThrusterWindow thrusterWindow;
    VehicleWizard wizard;
    QString settingsFile;
    QSettings *settings;
    QString currentVehicle;
    QString currentConfiguration;

    void updateVehicleConfigurationMenu();
    void checkFile(QString filename);
    SerialClient *serial_client;
    UdpClient *udp_client;

    //import from old interface
    void initializeDataUi();
    int thrustersCount;
    QList<QProgressBar *> thrusterBarGroup;
    QGraphicsScene *scene;

    // Interface for accessing UVState object
    IUserInterfaceData uv_interface;
private slots:
    void updateVehiclesMenu();

    //import from old interface
    void updateVehicleUi();
    void updateUi();

    void resetImu();
    void clearResetImu();

    // menu actions
    void createVehicle();
    void chooseVehicle(QAction *action);
    void chooseConfiguration(QAction *action);

    // full screen key combination
    void fullScreenKey();

    //Other buttons
    void reconnectcROVclick();

    void normalConnectionClick();
    void directConnectionClick();
    void configConnectionClick();

    void ConnectionTypeChanged(e_MessageTypes connectionType);

};

#endif // MAINWINDOW_H
