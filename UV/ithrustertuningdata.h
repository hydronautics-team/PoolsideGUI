#ifndef ITHRUSTERTUNINGDATA_H
#define ITHRUSTERTUNINGDATA_H

#include "ibasicdata.h"

/** \brief Interface for accessing data in UV_State to alter specific thruster parameters
 *
 */
class IThrusterTuningData : public IBasicData
{
public:
    IThrusterTuningData();

    UV_Thruster getThrusterData(unsigned int slot);
    void setThrusterData(unsigned int slot, UV_Thruster data);
};

#endif // ITHRUSTERTUNINGDATA_H
