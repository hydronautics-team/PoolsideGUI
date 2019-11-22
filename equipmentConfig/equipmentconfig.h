#ifndef EQUIPMENTCONFIG_H
#define EQUIPMENTCONFIG_H

#include "ui_equipmentconfig.h"

class equipmentConfig : public QWidget, private Ui::equipmentConfig
{
    Q_OBJECT

public:
    explicit equipmentConfig(QWidget *parent = nullptr);
};

#endif // EQUIPMENTCONFIG_H
