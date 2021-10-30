#include "ControlWindow.h"

ControlWindow::ControlWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ControlWindow) {
    ui->setupUi(this);
    ui->CheckBoxMouse3d->setCheckState(Qt::Checked); // TODO: сделать автоматическую установку дефолтного чекбокса
//    connect(ui->CheckBoxKeyBoard, SIGNAL(stateChanged(state)), this, SLOT(MainWindow::enableController(Control::KEYBOARD, state)));
    connect(ui->CheckBoxKeyBoard, SIGNAL(stateChanged(int)), this, SLOT(KeyboardSelection(int)));
    connect(ui->CheckBoxMouse3d, SIGNAL(stateChanged(int)), this, SLOT(Mouse3dSelection(int)));
    connect(ui->CheckBoxJoystickLogitech, SIGNAL(stateChanged(int)), this, SLOT(JoystickLogitechSelection(int)));
}

ControlWindow::~ControlWindow() {
    delete ui;
}

void ControlWindow::KeyboardSelection(int state) {
    emit controllersEnabelChanged(Control::KEYBOARD, state);
}
void ControlWindow::Mouse3dSelection(int state) {
    emit controllersEnabelChanged(Control::MOUSE3D, state);
}
void ControlWindow::JoystickLogitechSelection(int state) {
    emit controllersEnabelChanged(Control::JOYSTICK, state);
}

//void ControlWindow::Mouse3dSelection(bool selected) {
//    if (checked == true) {
////        MainWindow::controller.changeController(Control::MOUSE3D);
//
//        ui->CheckBoxKeyBoard->setEnabled(false);
//        ui->CheckBoxJoystickLogitech->setEnabled(false);
//    } else {
//        ui->CheckBoxKeyBoard->setEnabled(true);
//        ui->CheckBoxJoystickLogitech->setEnabled(true);
//    }
//}
//
//void ControlWindow::JoystickLogitechSelection(bool selected) {
//    if (checked == true) {
////        MainWindow::controller.changeController(Control::JOYSTICK);
//
//        ui->CheckBoxKeyBoard->setEnabled(false);
//        ui->CheckBoxMouse3d->setEnabled(false);
//    } else {
//        ui->CheckBoxKeyBoard->setEnabled(true);
//        ui->CheckBoxMouse3d->setEnabled(true);
//    }
//}
