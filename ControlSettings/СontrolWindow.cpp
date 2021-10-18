#include "СontrolWindow.h"

ControlWindow::ControlWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ControlWindow) {
    ui->setupUi(this);
}

ControlWindow::~ControlWindow() {
    delete ui;
}

void ControlWindow::on_CheckBoxKeyBoard_clicked(bool checked) {
    if (checked == true) {
        controller = new Keyboard("KeyBoard", 5);

        ui->CheckBox3dMouse->setEnabled(false);
        ui->CheckBoxJoystickLogitech->setEnabled(false);

        emit controlObject(controller);
    } else {
        delete controller;
        emit controlObject_del();

        ui->CheckBox3dMouse->setEnabled(true);
        ui->CheckBoxJoystickLogitech->setEnabled(true);
    }
}

void ControlWindow::on_CheckBox3dMouse_clicked(bool checked) {
    if (checked == true) {
        controller = new Mouse3d("3dMouse", 5);

        ui->CheckBoxKeyBoard->setEnabled(false);
        ui->CheckBoxJoystickLogitech->setEnabled(false);

        emit controlObject(controller);
    } else {
        delete controller;
        emit controlObject_del();

        ui->CheckBoxKeyBoard->setEnabled(true);
        ui->CheckBoxJoystickLogitech->setEnabled(true);
    }
}

void ControlWindow::on_CheckBoxJoystickLogitech_clicked(bool checked) {
    if (checked == true) {
        controller = new Joystick("Joystick", 10, 0);

        ui->CheckBoxKeyBoard->setEnabled(false);
        ui->CheckBox3dMouse->setEnabled(false);

        emit controlObject(controller);
    } else {
        delete controller;
        emit controlObject_del();

        ui->CheckBoxKeyBoard->setEnabled(true);
        ui->CheckBox3dMouse->setEnabled(true);
    }
}
