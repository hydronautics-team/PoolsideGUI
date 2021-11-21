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
    Thruster thrusters[8];

private:
    json thrusterJson;
    void createDefaultThrusterJson(std::string fileName);

    Ui::ThrusterWindow *ui;
};

#endif // THRUSTERWINDOW_H
