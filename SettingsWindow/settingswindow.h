#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "ui_settingswindow.h"
#include <QTimer>
#include <QVector>

class SettingsWindow : public QWidget, public Ui::SettingsWindow
{
    Q_OBJECT

signals:
    void updateVehicle();

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
    void timerTickEvent();
    void changeDevice(int device_id);

private:
    QTimer *timer;
    QTableWidget *table;
    QVector<unsigned int> joystick_list;
    int current_device;
    int current_joystick;
};

#endif // SETTINGSWINDOW_H
