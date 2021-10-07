#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "ui_settingswindow.h"
#include <QTimer>
#include <QVector>

#include "ControlSettings/Joystick.h"
#include "ControlSettings/Mouse3d.h"
#include "ControlSettings/controldevices.h"

class SettingsWindow : public QWidget, public Ui::SettingsWindow {
Q_OBJECT

signals:
    void updateVehicle();

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    ControlDevices* controldevices = nullptr;

public slots:
    void showPageConfigThruster();
    void showPageConfigRS();
    void showPageConfigSSH();
    void showPageConfigCoef();
    void showPageConfigControls();
    void showPageConfigView();
    void showPageAboutProgram();
    void showPageOtherSettings();
    void showControlDevices();
    void timerTickEvent();
    void changeDevice(int device_id);

signals:
    void controlConnect();

private:
    QTimer *timer;
    QTableWidget *table;
    QVector<unsigned int> joystick_list;
    int current_device;
    int current_joystick;
    ControlBase *controller;
};

#endif // SETTINGSWINDOW_H
