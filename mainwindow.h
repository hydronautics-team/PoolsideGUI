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
#include <QPixmap>


#include "KX_Pult/kx_protocol.h"
#include "KX_Pult/qkx_coeffs.h"

#include "ui_mainwindow.h"

#include "UV/iuserinterfacedata.h"
#include "Communication/SerialClient.h"
#include "Control/Joystick.h"
#include "ThrusterSettings/ThrusterWindow.h"
#include "StabilizationSettings/StabilizationWindow.h"

class MainWindow: public QMainWindow, private Ui::MainWindow {
    Q_OBJECT

signals:
    //import from old interface
    void updateCompass(double yaw);

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    Joystick* controller = nullptr;

    StabilizationWindow stabilizationWindow;
    ThrusterWindow thrusterWindow;

    void updateVehicleConfigurationMenu();
    void checkFile(QString filename);
    SerialClient* serial_client;

    IUserInterfaceData uv_interface;
private slots:
    // void updateVehiclesMenu();
    void stabilizeRollToggled(bool state);
    void stabilizePitchToggled(bool state);
    void stabilizeYawToggled(bool state);
    void stabilizeDepthToggled(bool state);

    void normalPackageClick();
    void configPackageClick();
    void directPackageClick();

    void updateUi();

    void resetImu();
    void clearResetImu();

    // menu actions
    // void createVehicle();
    // void chooseVehicle(QAction *action);
    // void chooseConfiguration(QAction *action);

    // full screen key combination
    void fullScreenKey();

    //Other buttons
    // void reconnectcROVclick();


    // void ConnectionTypeChanged(e_MessageTypes connectionType);

};

#endif // MAINWINDOW_H
