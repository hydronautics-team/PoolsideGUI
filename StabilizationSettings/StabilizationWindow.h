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

    enum ContourName {
        YAW = 0,
        ROLL = 1,
        PITCH = 2,
        DEPTH = 3,
        MARCH = 4,
        LAG = 5
    };

    int controlContour_amount;
    ContourName currentContour;
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


private slots:
    void updateStabilizationStateUi();
    void saveToJsonFile();
    void ContourChanged();
    void ContourEdited();

};

#endif // STABILIZATIONSETTINGS_H
