#include "ControlBase.h"
#include <QDebug>

ControlBase::ControlBase(QString name, int update_time) {
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

double ControlBase::Sensitivity(double value, double deadZone, double maxValue) {
    double result = 0;
    if ((abs(value) < deadZone) || (abs(value) > 100)) { result = 0; }
    else {
        result = ((maxValue) / (100 - deadZone)) * (abs(value) - deadZone);
        if (value < 0) { result = -result; }
    }
    return result * 320;
}

double ControlBase::Sensitivity(double value, double deadZone, double pointX, double pointY, double maxValue) {
    double result = 0;
    double x = value;
    double x1 = deadZone;
    double x2 = pointX;
    double x3 = 100;

    if ((abs(value) < deadZone) || (abs(value) > 100)) { result = 0; }
    else {
        double t = (-qSqrt(abs(x) * x1 - 2 * abs(x) * x2 + abs(x) * x3 - x1 * x3 + x2 * x2) - x1 + x2) /
                   (-x1 + 2 * x2 - x3);
        result = (1 - t) * (1 - t) * 0 + 2 * (1 - t) * t * pointY + t * t * maxValue;
        if (value < 0) { result = -result; }
    }
    return result * 320;
}

