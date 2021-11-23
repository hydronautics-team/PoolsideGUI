#ifndef THRUSTERWINDOW_H
#define THRUSTERWINDOW_H

#include <QWidget>
#include <QDebug>
#include <string>


#include <iostream>
#include <iomanip>
#include <fstream>
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

    int thrusters_amount;
    Thruster *thrusters;
    std::ifstream file;

private:
    json thrusterJson;
    void createDefaultThrusterJson(std::string fileName);

//    struct ThrusterName_number {
//        QString name;
//        int number;
//    };
//    ThrusterName_number *thrusters_table;

    Ui::ThrusterWindow *ui;
};

#endif // THRUSTERWINDOW_H
