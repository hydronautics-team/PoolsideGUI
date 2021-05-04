#ifndef THRUSTERSETTINGS_H
#define THRUSTERSETTINGS_H

#include <QSettings>
#include <QPushButton>
#include <QButtonGroup>
#include "ui_thrustersettings.h"

#include "UV/ituningdata.h"

class ThrusterSettings : public QWidget, private Ui::ThrusterSettings
{
    Q_OBJECT

public:
    explicit ThrusterSettings(QWidget *parent = nullptr);

signals:
    void flashVehicle();
    void ThrusterChanged(unsigned int slot);

public slots:
    void updateVehicle();

private:
    ITuningData uv_interface;
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
    void flashButtonClicked();
    void sliderVelocityChanged(int value);
    void sliderKForwardChanged(int value);
    void sliderKBackwardChanged(int value);
    void sliderForwardSaturationChanged(int value);
    void sliderBackwardSaturationChanged(int value);
    void spinBoxVelocityChanged(int value);
    void spinBoxKForwardChanged(double value);
    void spinBoxKBackwardChanged(double value);
    void spinBoxForwardSaturationChanged(int value);
    void spinBoxBackwardSaturationChanged(int value);
};

#endif // THRUSTERSETTINGS_H
