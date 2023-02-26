#include "uv_state.h"

ImuData::ImuData() {
    roll = 0;
    pitch = 0;
    yaw = 0;
    rollSpeed = 0;
    pitchSpeed = 0;
    yawSpeed = 0;
    depth = 0;
}

ControlData::ControlData() {
    march = 0;
    lag = 0;
    depth = 0;
    roll = 0;
    pitch = 0;
    yaw = 0;
};

UV_State::UV_State() {
    resetImu = false;

    stabRoll    = false;
    stabYaw     = false;
    stabPitch   = false;
    stabDepth   = false;
}

UV_State::~UV_State() {
    if (thruster != nullptr) {
        delete[] thruster;
    }
    if (controlContour != nullptr) {
        delete[] controlContour;
    }
}

void UV_State::setThrusterAmount(int thrusterAmount) {
    if (thruster != nullptr) {
        delete thruster;
    }
    thruster = new UV_Thruster[thrusterAmount];
    this->thrusterAmount = thrusterAmount;
    qDebug() << "setThrusterAmount " << thrusterAmount;
}

int UV_State::getThrusterAmount() {
    return thrusterAmount;
}
