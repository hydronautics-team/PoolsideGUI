#include "ControlWindow.h"

ControlWindow::ControlWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ControlWindow) {
    ui->setupUi(this);
//    connect(ui->CheckBoxKeyBoard, SIGNAL(stateChanged(state)), this, SLOT(MainWindow::enableController(Control::KEYBOARD, state)));
//    connect(ui->CheckBoxKeyBoard, SIGNAL(stateChanged(state)), this, SLOT(KeyboardSelection(state)));
//    connect(ui->CheckBoxMouse3d, SIGNAL(stateChanged(state)), this, SLOT(Mouse3dSelection(state)));
//    connect(ui->CheckBoxJoystickLogitech, SIGNAL(stateChanged(state)), this, SLOT(JoystickLogitechSelection(state)));

}

ControlWindow::~ControlWindow() {
    delete ui;
}
//
//void ControlWindow::KeyboardSelection(bool selected) {
//        emit MainWindow::enableController(Control::KEYBOARD, selected);
//}

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
