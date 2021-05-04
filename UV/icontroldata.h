#ifndef ICONTROLDATA_H
#define ICONTROLDATA_H

#include "ibasicdata.h"

class IControlData : public IBasicData
{
public:
    IControlData();

    void setControlData(ControlData data);

    void setMarch(double march);
    void setLag(double lag);
    void setDepth(double depth);
    void setRoll(double roll);
    void setPitch(double pitch);
    void setYaw(double yaw);

    void setDeviceVelocity(int slot, double velocity);
};

#endif // ICONTROLDATA_H
