#include "iuserinterfacedata.h"

#include <stdexcept>

IUserInterfaceData::IUserInterfaceData()
    : IBasicData()
{

}

ControlData IUserInterfaceData::getControlData()
{
    ControlData data;
    UVMutex.lock();
    data = UVState.control;
    UVMutex.unlock();
    return data;
}

ImuData IUserInterfaceData::getImuData()
{
    ImuData data;
    UVMutex.lock();
    data = UVState.imu;
    UVMutex.unlock();
    return data;
}

UV_Device IUserInterfaceData::getDeviceData(QString name)
{
    UV_Device data;
    UVMutex.lock();

    for(unsigned int i=0; i<UVState.devices_amount; i++) {
        if(name == UVState.device[i].name) {
            data = UVState.device[i];
        }
        else {
            std::string error = "There is no UV_device with the name: " + name.toStdString();
            throw std::invalid_argument(error);
        }
    }

    UVMutex.unlock();
    return data;
}

UV_Thruster IUserInterfaceData::getThrusterData(QString name)
{
    UV_Thruster data;
    UVMutex.lock();

    for(unsigned int i=0; i<UVState.devices_amount; i++) {
        if(name == UVState.thruster[i].name) {
            data = UVState.thruster[i];
        }
        else {
            std::string error = "There is no UV_device with the name: " + name.toStdString();
            throw std::invalid_argument("There is no UV_device by this name");
        }
    }

    UVMutex.unlock();
    return data;
}

double IUserInterfaceData::getDeviceVelocity(int slot)
{
    if(static_cast<unsigned int>(slot) >= sizeof(UVState.device)/sizeof(UVState.device[0])) {
        return 0;
    }

    double data = 0;

    UVMutex.lock();

    data = UVState.device[slot].velocity;

    UVMutex.unlock();
    return data;
}
