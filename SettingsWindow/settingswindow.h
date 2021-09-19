#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "ui_settingswindow.h"
#include <QTimer>
#include <QVector>

#include "Drivers/joystick.h"
#include "Drivers/mouse_3d.h"
#include "SettingsWindow/SetConfiguration/setconfiguration.h"

class SettingsWindow : public QWidget, public Ui::SettingsWindow
{
    Q_OBJECT

signals:
    void updateVehicle();

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();// объявление деструктора для удаления объекта настройки конфигураций

public slots:
    void showPageConfigThruster();
    void showPageConfigRS();
    void showPageConfigSSH();
    void showPageConfigCoef();
    void showPageConfigControls();
    void showPageConfigView();
    void showPageAboutProgram();
    void showPageOtherSettings();
    void showSetConfiguration();
    void timerTickEvent();
    void changeDevice(int device_id);

signals:
    void controllerChanged(unsigned int id, QString name);

private:
    QTimer *timer;
    QTableWidget *table;
    setConfiguration* config; // объект класса конфигураций
    QVector<unsigned int> joystick_list;
    int current_device;
    int current_joystick;
    ControlBase *controller;
};

#endif // SETTINGSWINDOW_H
