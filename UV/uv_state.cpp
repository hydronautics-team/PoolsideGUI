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
    udpHostAddress = "127.0.0.1";
    udpHostPort = 7755;

    resetImu = false;

    stabRoll = false;
    stabYaw = false;
    stabPitch = false;
    stabDepth = false;
}

UV_State::~UV_State() {
    if (thruster != nullptr) {
        delete[] thruster;
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

void UV_State::setThrusterNext() {
    if (currentThruster < thrusterAmount - 1) {
        currentThruster++;
    } else {
        currentThruster = 0;
    }
}
