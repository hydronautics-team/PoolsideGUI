#ifndef ITHRUSTERTUNINGDATA_H
#define ITHRUSTERTUNINGDATA_H

#include "ibasicdata.h"

#include <QDebug>
/** \brief Interface for accessing data in UV_State to alter specific thruster parameters
 *
 */
class ITuningData : public IBasicData {
public:
    ITuningData();

    void setThrusterAmount(int thrusterAmount);
    int getThrusterAmount();
    UV_Thruster getThrusterData(unsigned int slot);
    void setThrusterData(unsigned int slot, UV_Thruster data);
    void setThrusterPower(unsigned int slot, bool power);

    UV_ControlContour getControlContourData(unsigned int slot);
    void setControlContourData(unsigned int slot, UV_ControlContour data);
};

#endif // ITHRUSTERTUNINGDATA_H
