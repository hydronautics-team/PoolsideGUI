#ifndef ICONTROLDATA_H
#define ICONTROLDATA_H

#include "ibasicdata.h"

class IControlData : public IBasicData
{
public:
    IControlData();

    void setControlData(ControlData data);
};

#endif // ICONTROLDATA_H
