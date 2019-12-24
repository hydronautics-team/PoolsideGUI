#ifndef THRUSTERSETTINGS_H
#define THRUSTERSETTINGS_H

#include <QSettings>
#include <QPushButton>
#include "ui_thrustersettings.h"

class ThrusterSettings : public QWidget, private Ui::ThrusterSettings
{
    Q_OBJECT

public:
    explicit ThrusterSettings(QWidget *parent = nullptr);

signals:
    void updateVehicle();

public slots:
    void updateThrusterButtons();

private:
    QString settingsFile;
    QSettings *settings;
    QString currentVehicle;

    void clearWidgets(QLayout * layout);
};

#endif // THRUSTERSETTINGS_H
