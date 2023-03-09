#ifndef IUSERINTERFACEDATA_H
#define IUSERINTERFACEDATA_H

#include "ibasicdata.h"
#include "uv_state.h"

class IUserInterfaceData: public IBasicData {
public:
    IUserInterfaceData();

    ControlData getControlData();
    ImuData getImuData();
    double getDeviceVelocity(e_Device device);

    void setPackegeMode(e_packageMode packageMode);
    void setConnectionMode(e_Connection connectionMode);
    e_Connection getConnectionMode();

    void setStabRoll(bool value);
    void setStabPitch(bool value);
    void setStabYaw(bool value);
    void setStabDepth(bool value);

    void setResetImu(bool value);
    void setThrustersON(bool value);

};

#endif // IUSERINTERFACEDATA_H
