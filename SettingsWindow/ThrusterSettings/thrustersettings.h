#ifndef THRUSTERSETTINGS_H
#define THRUSTERSETTINGS_H

#include "ui_thrustersettings.h"

class ThrusterSettings : public QWidget, private Ui::ThrusterSettings
{
    Q_OBJECT

public:
    explicit ThrusterSettings(QWidget *parent = nullptr);
};

#endif // THRUSTERSETTINGS_H
