#include "icontroldata.h"

IControlData::IControlData():
    IBasicData() {

}

void IControlData::setControlData(ControlData data) {
    UVMutex.lock();
    UVState.control = data;
    UVMutex.unlock();
}

void IControlData::setMarch(double march) {
    UVMutex.lock();
    UVState.control.march = march;
    UVMutex.unlock();
}

void IControlData::setLag(double lag) {
    UVMutex.lock();
    UVState.control.lag = lag;
    UVMutex.unlock();
}

void IControlData::setDepth(double depth) {
    UVMutex.lock();
    UVState.control.depth = depth;
    UVMutex.unlock();
}

void IControlData::setRoll(double roll) {
    UVMutex.lock();
    UVState.control.roll = roll;
    UVMutex.unlock();
}

void IControlData::setPitch(double pitch) {
    UVMutex.lock();
    UVState.control.pitch = pitch;
    UVMutex.unlock();
}

void IControlData::setYaw(double yaw) {
    UVMutex.lock();
    UVState.control.yaw = yaw;
    UVState.integratedYaw += yaw/10000;
    UVMutex.unlock();
}

void IControlData::setDeviceVelocity(e_Device device, double velocity) {
    UVMutex.lock();
    UVState.device[device].velocity = velocity;
    UVMutex.unlock();
}

void IControlData::setDepthIntegration(float value) {
    UVMutex.lock();
    if (UVState.integratedDepth < 3.86) {
            UVState.integratedDepth += (value / 150);
    } else {
        UVState.integratedDepth = 3.86;
    }

    UVMutex.unlock();
}

void IControlData::setThrustersON(int thrustersON) {
    UVMutex.lock();
    if (thrustersON < 0) {
        UVState.thrustersON = false;
    } else {
        UVState.thrustersON = true;
    }
    UVMutex.unlock();
}
