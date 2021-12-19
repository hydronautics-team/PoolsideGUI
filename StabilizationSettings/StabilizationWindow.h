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

    int thrusters_amount;
    UV_ControlContour *ControlContour;
    std::ifstream file;

private:
    json allStabilizationJson;

    void createDefaultStabilizationJson();

    Ui::StabilizationWindow *ui;
    ITuningData interface;
};

#endif // STABILIZATIONSETTINGS_H
