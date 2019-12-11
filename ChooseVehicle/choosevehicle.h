#ifndef CHOOSEVEHICLE_H
#define CHOOSEVEHICLE_H

#include "ui_choosevehicle.h"

class ChooseVehicle : public QDialog, private Ui::ChooseVehicle
{
    Q_OBJECT

public:
    explicit ChooseVehicle(QWidget *parent = nullptr);
};

#endif // CHOOSEVEHICLE_H
