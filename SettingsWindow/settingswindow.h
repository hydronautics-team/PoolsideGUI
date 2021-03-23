#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "ui_settingswindow.h"
#include <QTimer>
#include <QGamepad>

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

private:
    QTimer *timer;

    QTableWidget *table;

    QGamepad gamepad;
};

#endif // SETTINGSWINDOW_H
