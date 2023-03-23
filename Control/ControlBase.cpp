#include "ControlBase.h"
#include <QDebug>

ControlBase::ControlBase(QString name) {
    device_name = name;
}

void ControlBase::sendAction(e_actionTypes type, float value) {
    switch (type) {
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

    case TILT:
        setTilt(static_cast<int8_t>(value));
        break;
    }
}

void ControlBase::sendAction(e_actionTypes type, int8_t value) {
    switch (type) {
    case GRAB:
        setGrab(value);
        break;

    case GRAB_ROTATE:
        setGrabRotate(value);
        break;

    case DEPTH_SENSOR:
        setDepthSensor(value);
        break;

    case THRUSTERS_ON:
        setThrustersON(value);
        break;
    }
}

void ControlBase::setMarch(float value) {
    interface.setMarch(value);
}

void ControlBase::setLag(float value) {
    interface.setLag(value);
}

void ControlBase::setDepth(float value) {
    interface.setDepth(value);
}

void ControlBase::setRoll(float value) {
    interface.setRoll(value);
}

void ControlBase::setPitch(float value) {
    interface.setPitch(value);
}

void ControlBase::setYaw(float value) {
    interface.setYaw(value);
}

void ControlBase::setGrab(int8_t value) {
    interface.setDeviceVelocity(e_Device::DEVICE_GRAB, value);
}

void ControlBase::setGrabRotate(int8_t value) {
    interface.setDeviceVelocity(e_Device::DEVICE_GRAB_ROTATE, value);
}

void ControlBase::setTilt(int8_t value) {
    interface.setDeviceVelocity(e_Device::DEVICE_TILT, value);
}

void ControlBase::setDepthSensor(int8_t value) {
    interface.setDepthIntegration(value);
}

void ControlBase::setThrustersON(int8_t value) {
    if (value != 0) {
        interface.setThrustersON(value);
    }
    // qDebug() << " setThrustersON " << value;
}
