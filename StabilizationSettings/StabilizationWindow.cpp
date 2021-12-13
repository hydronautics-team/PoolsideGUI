#include "StabilizationWindow.h"
#include "ui_StabilizationWindow.h"

StabilizationWindow::StabilizationWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::StabilizationWindow) {
    ui->setupUi(this);
    this->setStyleSheet("background: url(:/images/images/ControlSystem.png)");

}

StabilizationWindow::~StabilizationWindow() {
    delete ui;
}
