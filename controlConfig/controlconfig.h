#ifndef CONTROLCONFIG_H
#define CONTROLCONFIG_H

#include "ui_controlconfig.h"

class controlConfig : public QWidget, private Ui::controlConfig
{
    Q_OBJECT

public:
    explicit controlConfig(QWidget *parent = nullptr);
};

#endif // CONTROLCONFIG_H
