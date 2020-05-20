#include "icontroldata.h"

IControlData::IControlData() :
    IBasicData()
{

}

void IControlData::setControlData(ControlData data)
{
    UVMutex.lock();
    UVState.control = data;
    UVMutex.unlock();
}
