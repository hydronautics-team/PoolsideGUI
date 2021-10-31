#include "Thruster.h"
#include "ui_Thruster.h"

Thruster::Thruster(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Thruster) {
    ui->setupUi(this);
}

Thruster::~Thruster() {
    delete ui;
}
