#include "ThrusterWindow.h"
#include "ui_ThrusterWindow.h"

ThrusterWindow::ThrusterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThrusterWindow)
{
    ui->setupUi(this);

    thrusters_amount = sizeof(thrusters) / sizeof(thrusters[0]);
    for (int i = 0; i < thrusters_amount; ++i) {
        ui->horizontalLayout_Thrusters->addWidget(&thrusters[i], i);
    }


}

ThrusterWindow::~ThrusterWindow()
{
    delete ui;
}
