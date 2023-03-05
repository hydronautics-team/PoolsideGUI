#ifndef STABILIZATIONSETTINGS_H
#define STABILIZATIONSETTINGS_H

#include <QWidget>
#include <QDebug>
#include <QTimer>

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Utilitis/json.h"
#include "UV/ituningdata.h"

// #include "KX_Pult/kx_protocol.h"
// #include "KX_Pult/qkx_coeffs.h"

using json = nlohmann::json;

namespace Ui {
    class StabilizationWindow;
}

class StabilizationWindow: public QWidget {
    Q_OBJECT

public:
    explicit StabilizationWindow(QWidget* parent = nullptr);

    // ~StabilizationWindow();


private:
    Ui::StabilizationWindow* ui;
    ITuningData interface;

    QString jsonName;
    std::ifstream file;
    json allStabilizationJson;

    // x_protocol* X_Protocol;
    e_Countour currentContour;
    UV_StabilizationConstants ConstantsControlContour[6];
    UV_StabilizationState StateControlContour[6];

    void FillUiConstants();
    void FillUiStates();

    void createDefaultStabilizationJson();
    void saveToFile();

    void getConstantsFromJson();

private slots:
    // void updateVariables_KX();

    void ContourChangedYaw();
    void ContourChangedRoll();
    void ContourChangedPitch();
    void ContourChangedDepth();
    void ContourChangedMarch();
    void ContourChangedLag();

    void ContourEdited();
};

#endif // STABILIZATIONSETTINGS_H
