#ifndef STABILIZATIONSETTINGS_H
#define STABILIZATIONSETTINGS_H

#include <QWidget>
#include <QDebug>
#include <string>


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
    UV_ControlContour *ControlContour;
    std::ifstream file;

private:
    json allStabilizationJson;

    void createDefaultStabilizationJson();
    void setUV_ControlContour(int number, json StabilizationJson);


    Ui::StabilizationWindow *ui;
    ITuningData interface;

public slots:

    void ContourChanged();
    void ContourEdited();

};

#endif // STABILIZATIONSETTINGS_H
