#ifndef THRUSTERSETTINGS_H
#define THRUSTERSETTINGS_H

#include <QSettings>
#include <QPushButton>
#include <QButtonGroup>
#include "ui_thrustersettings.h"

class ThrusterSettings : public QWidget, private Ui::ThrusterSettings
{
    Q_OBJECT

public:
    explicit ThrusterSettings(QWidget *parent = nullptr);

signals:
    void updateVehicle();
    void flashVehicle();

public slots:
    void updateThrusterSettings();

private:
    QString settingsFile;
    QSettings *settings;
    QString currentVehicle;
    int currentThruster;
    int thrustersCount;
    QButtonGroup *thrusterButtonGroup;

private slots:
    void thrusterButtonClicked(int value);
    void thrusterIdChanged(int value);
    void thrusterReverseEnabled(int state);
    void thrusterVelocityChanged(int value);
    void thrusterKForwardChanged(int value);
    void thrusterKBackwardChanged(int value);
    void thrusterForwardSaturationChanged(int value);
    void thrusterBackwardSaturationChanged(int value);
};

#endif // THRUSTERSETTINGS_H
