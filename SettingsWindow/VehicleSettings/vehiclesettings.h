#ifndef VEHICLESETTINGS_H
#define VEHICLESETTINGS_H

#include "ui_vehiclesettings.h"

#include <QWidget>

#include "UV/ituningdata.h"

#include "KX_Pult/kx_protocol.h"
#include "KX_Pult/qkx_coeffs.h"

class VehicleSettings : public QWidget, private Ui::VehicleSettings {
Q_OBJECT

public:
    explicit VehicleSettings(QWidget *parent = nullptr);

public slots:
    void updateData();

    void on_radioButton_CS_YawSelect_released();
    void on_radioButton_CS_DepthSelect_released();
    void on_radioButton_CS_RollSelect_released();
    void on_radioButton_CS_PitchSelect_released();
    void on_radioButton_CS_MarchSelect_released();
    void on_radioButton_CS_LagSelect_released();

private:
    ITuningData *uv_interface;

    unsigned int current_contour;

    x_protocol *X_Protocol;

    void updateLabels();
    void updateSpinboxes();
    void saveSpinboxes();
    void updateVariables_KX();
};

#endif // VEHICLESETTINGS_H
