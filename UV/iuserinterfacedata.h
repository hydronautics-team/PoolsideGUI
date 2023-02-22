#ifndef IUSERINTERFACEDATA_H
#define IUSERINTERFACEDATA_H

#include "ibasicdata.h"

class IUserInterfaceData : public IBasicData {
public:
    IUserInterfaceData();

    ControlData getControlData();
    ImuData getImuData();
    UV_Device getDeviceData(QString name);
    UV_Thruster getThrusterData(QString name);

    double getDeviceVelocity(int slot);

    void setResetImuValue(bool value);
};

#endif // IUSERINTERFACEDATA_H
