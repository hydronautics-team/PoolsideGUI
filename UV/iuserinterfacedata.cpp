#include "iuserinterfacedata.h"

IUserInterfaceData::IUserInterfaceData()
    : IBasicData() {

}

ControlData IUserInterfaceData::getControlData() {
    ControlData data;

    UVMutex.lock();
    data = UVState.control;
    UVMutex.unlock();

    return data;
}

ImuData IUserInterfaceData::getImuData() {
    ImuData data;

    UVMutex.lock();
    data = UVState.imu;
    UVMutex.unlock();

    return data;
}

double IUserInterfaceData::getDeviceVelocity(e_Device device) {
    double data;

    UVMutex.lock();
    data = UVState.device[device].velocity;
    UVMutex.unlock();

    return data;
}

void IUserInterfaceData::setPackegeMode(e_packageMode packageMode) {
    UVMutex.lock();
    UVState.packageMode = packageMode;
    UVMutex.unlock();
}

void IUserInterfaceData::setStabRoll(bool value) {
    UVMutex.lock();
    UVState.stabRoll = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setStabPitch(bool value) {
    UVMutex.lock();
    UVState.stabPitch = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setStabYaw(bool value) {
    UVMutex.lock();
    UVState.stabYaw = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setStabDepth(bool value) {
    UVMutex.lock();
    UVState.stabDepth = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setResetImu(bool value) {
    UVMutex.lock();
    UVState.resetImu = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setThrustersON(bool value) {
    UVMutex.lock();
    UVState.thrustersON = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setConnectionMode(e_Connection connectionMode) {
    UVMutex.lock();
    UVState.connectionMode = connectionMode;
    UVMutex.unlock();
}
