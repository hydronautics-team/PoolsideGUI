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
    void flashVehicle();

public slots:
    void updateVehicle();

private:
    QString settingsFile;
    QSettings *settings;
    QString currentVehicle;
    int currentThruster;
    int thrustersCount;
    QButtonGroup *thrusterButtonGroup;

private slots:
    void updateThrusterSettings();
    void thrusterButtonClicked(int value);
    void thrusterIdChanged(int value);
    void thrusterReverseChanged(int state);
    void thrusterVelocityChanged(int value);
    void thrusterKForwardChanged(int value);
    void thrusterKBackwardChanged(int value);
    void thrusterForwardSaturationChanged(int value);
    void thrusterBackwardSaturationChanged(int value);
};

#endif // THRUSTERSETTINGS_H
