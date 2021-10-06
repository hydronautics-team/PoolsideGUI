#include "controldevices.h"
#include "ui_controldevices.h"

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

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void ControlDevices::on_checkBox_3dMouse_clicked(bool checked)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void ControlDevices::on_checkBox_JoystickLogitech_clicked(bool checked)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
