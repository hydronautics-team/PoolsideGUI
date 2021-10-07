#include "controldevices.h"
#include "ui_controldevices.h"

#include "Keyboard.h"
#include "Mouse3d.h"
#include "Joystick.h"

ControlDevices::ControlDevices(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlDevices)
{
    ui->setupUi(this);
}

ControlDevices::~ControlDevices()
{
    delete ui;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void ControlDevices::on_checkBox_KeyBoard_clicked(bool checked)
{
    if(checked == true)
    {
        controller = new Keyboard("KeyBoard", 5);

        ui->checkBox_3dMouse->setEnabled(false);
        ui->checkBox_JoystickLogitech->setEnabled(false);

        emit controlObject(controller);
    }
    else
    {
        delete controller;
        emit controlObject_del();
        ui->checkBox_3dMouse->setEnabled(true);
        ui->checkBox_JoystickLogitech->setEnabled(true);
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void ControlDevices::on_checkBox_3dMouse_clicked(bool checked)
{
    if(checked == true)
    {
        controller = new Mouse3d("3dMouse", 5);

        ui->checkBox_KeyBoard->setEnabled(false);
        ui->checkBox_JoystickLogitech->setEnabled(false);

        emit controlObject(controller);
    }
    else
    {
        delete controller;
        emit controlObject_del();
        ui->checkBox_KeyBoard->setEnabled(true);
        ui->checkBox_JoystickLogitech->setEnabled(true);
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void ControlDevices::on_checkBox_JoystickLogitech_clicked(bool checked)
{

    if(checked == true)
    {
        controller = new Joystick("Joystick", 10, 0);

        ui->checkBox_KeyBoard->setEnabled(false);
        ui->checkBox_3dMouse->setEnabled(false);

        emit controlObject(controller);
    }
    else
    {
        delete controller;
        emit controlObject_del();
        ui->checkBox_KeyBoard->setEnabled(true);
        ui->checkBox_3dMouse->setEnabled(true);
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
