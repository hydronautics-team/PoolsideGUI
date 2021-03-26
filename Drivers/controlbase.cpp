#include "controlbase.h"

ControlBase::ControlBase(QString name, int update_time)
{
    device_name = name;
}

void ControlBase::sendAction(e_actionTypes type, double value)
{
    switch(type) {
    case SET_MARCH:
        setMarch(value);
        break;

    case SET_LAG:
        setLag(value);
        break;

    case SET_DEPTH:
        setDepth(value);
        break;

    case SET_ROLL:
        setRoll(value);
        break;

    case SET_PITCH:
        setPitch(value);
        break;

    case SET_YAW:
        setYaw(value);
        break;

    case CLENCH_GRAB:
        clenchGrab(value);
        break;

    case UNCLENCH_GRAB:
        unclenchGrab(value);
        break;

    case ROTATE_GRAB_RIGHT:
        rotateGrabRight(value);
        break;

    case ROTATE_GRAB_LEFT:
        rotateGrabLeft(value);
        break;

    case ROTATE_TILT_UP:
        rotateTiltUp(value);
        break;

    case ROTATE_TILT_DOWN:
        rotateTiltDown(value);
        break;
    }
}

void ControlBase::setMarch(double value)
{
    interface.setMarch(value);
}

void ControlBase::setLag(double value)
{
    interface.setLag(value);
}

void ControlBase::setDepth(double value)
{
    interface.setDepth(value);
}

void ControlBase::setRoll(double value)
{
    interface.setRoll(value);
}

void ControlBase::setPitch(double value)
{
    interface.setPitch(value);
}

void ControlBase::setYaw(double value)
{
    interface.setYaw(value);
}

void ControlBase::clenchGrab(double value)
{
    interface.setDeviceVelocity(UV_Device::DEVICE_GRAB, value);
}

void ControlBase::unclenchGrab(double value)
{
    interface.setDeviceVelocity(UV_Device::DEVICE_GRAB, -value);
}

void ControlBase::rotateGrabRight(double value)
{
    interface.setDeviceVelocity(UV_Device::DEVICE_GRAB_ROTATE, value);
}

void ControlBase::rotateGrabLeft(double value)
{
    interface.setDeviceVelocity(UV_Device::DEVICE_GRAB_ROTATE, -value);
}

void ControlBase::rotateTiltUp(double value)
{
    interface.setDeviceVelocity(UV_Device::DEVICE_TILT, value);
}

void ControlBase::rotateTiltDown(double value)
{
    interface.setDeviceVelocity(UV_Device::DEVICE_TILT, -value);
}
