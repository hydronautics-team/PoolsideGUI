#ifndef STABILIZATIONSETTINGS_H
#define STABILIZATIONSETTINGS_H

#include <QWidget>
#include <QDebug>
#include <string>
#include <QTimer>


#include <iostream>
#include <iomanip>
#include <fstream>

#include "UV/ituningdata.h"
#include "Utilitis/json.h"

#include "UV/ituningdata.h"

#include "KX_Pult/kx_protocol.h"
#include "KX_Pult/qkx_coeffs.h"

using json = nlohmann::json;

namespace Ui {
    class StabilizationWindow;
}

class StabilizationWindow : public QWidget {
Q_OBJECT

public:
    explicit StabilizationWindow(QWidget *parent = nullptr);

    ~StabilizationWindow();

    QString jsonName;

    int controlContour_amount;
    STABILIZATION_CONTOURS currentContour;
    UV_StabilizationConstants *ConstantsControlContour;
    UV_StabilizationState *StateControlContour;
    std::ifstream file;

private:
    QTimer *updateStabilizationState;
    json allStabilizationJson;

    void createDefaultStabilizationJson();
    void setUV_ControlContour(int number, json StabilizationJson);


    Ui::StabilizationWindow *ui;
    ITuningData interface;

    x_protocol *X_Protocol;


private slots:
    void updateStabilizationStateUi();
    void updateVariables_KX();
    void saveToJsonFile();
    void ContourChanged();
    void ContourEdited();

};

#endif // STABILIZATIONSETTINGS_H
