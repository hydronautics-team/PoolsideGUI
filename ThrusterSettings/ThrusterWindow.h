#ifndef THRUSTERWINDOW_H
#define THRUSTERWINDOW_H

#include <QWidget>

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
    Ui::ThrusterWindow *ui;
};

#endif // THRUSTERWINDOW_H
