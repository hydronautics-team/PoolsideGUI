#ifndef THRUSTER_H
#define THRUSTER_H
#include "UV/uv_thruster.h"
#include <QWidget>
#include <string>
#include <QString>
#include <fstream>
#include <QDebug>
#include <iostream>

#include "Utilitis/json.h"
using json = nlohmann::json;

namespace Ui {
    class Thruster;
}

class Thruster : public QWidget {
Q_OBJECT

public:
    explicit Thruster(QWidget *parent = nullptr);

    ~Thruster();

    UV_Thruster getUV_Thruster();

private:
    UV_Thruster ThisThruster; //TODO: переделать под работу с UV_State
    json ThrusterJson;
    Ui::Thruster *ui;

    void setUV_Thruster();
    void setUi();

    bool power;

signals:
    void speedSpinBoxChange(int);
    void parametorsChanged(json json, UV_Thruster thruster);
    void powerChanged(int slot, bool power);

public slots:
    void setThruster(int number, json ThrusterJson);

private slots:
    void powerCheckBoxChanged(int power);

    void idChanged(int id);
    void speedChanged(int speed);
    void forwardKChanged(double forwardK);
    void backwardKChanged(double backwardK);
    void forwardSaturationChanged(int forwardSaturation);
    void backwardSaturationChanged(int backwardSaturation);
    void reverseChanged(int state);

    void speedSetForward();
    void speedSetStop();
    void speedSetBackward();
};

#endif // THRUSTER_H
