#include "ibasicdata.h"

IBasicData::IBasicData(UV_State *target, QMutex *target_mutex)
{
    state = target;
    mutex = target_mutex;
}

void IBasicData::getData()
{
    mutex->lock();
    internal_state = *state;
    mutex->unlock();
}

UV_State* IBasicData::gainAccess()
{
    mutex->lock();
    return state;
}

void IBasicData::closeAccess()
{
    mutex->unlock();
}
