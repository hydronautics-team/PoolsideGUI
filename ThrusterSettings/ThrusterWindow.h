#ifndef THRUSTERWINDOW_H
#define THRUSTERWINDOW_H

#include <QWidget>
#include <QDebug>
#include <string>


#include <iostream>
#include <iomanip>
#include <fstream>

#include "UV/ituningdata.h"
#include "Utilitis/json.h"
using json = nlohmann::json;

#include "Thruster.h"

namespace Ui {
class ThrusterWindow;
}

class ThrusterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ThrusterWindow(QWidget *parent = nullptr);
    ~ThrusterWindow();

    QString jsonName;

    int thrusters_amount;
    Thruster *thrusters;
    std::ifstream file;

private:
    json allThrusterJson;
    void createDefaultThrusterJson();
    Ui::ThrusterWindow *ui;
    ITuningData interface;

public slots:
    void thrusterEdited(json thrusterJson, UV_Thruster thruster);
//    void powerEdited(int slot, bool power);

};

#endif // THRUSTERWINDOW_H
