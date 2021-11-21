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

    QString name;

private:
    UV_Thruster ThisThruster;
    json ThisThrusterJson;
    Ui::Thruster *ui;

signals:
    void speedSpinBoxChange(int);
    UV_Thruster ThrusterDataChanged();

public slots:
    void setThruster(int number);
    void speedSetForward();
    void speedSetStop();
    void speedSetBackward();
};

#endif // THRUSTER_H
