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
    void setThrusterData(int slot, UV_Thruster data);
    UV_Thruster getThrusterData(int slot);
    void setThrusterPower(int slot, bool power);

    UV_StabilizationState getControlContourState(e_Countour countour);
    void setControlContourConstants(UV_StabilizationConstants constants);
    void setControlContourConstants(UV_StabilizationConstants constants, e_Countour countour);
    void setCurrentControlContour(e_Countour contour);
};

#endif // ITHRUSTERTUNINGDATA_H
