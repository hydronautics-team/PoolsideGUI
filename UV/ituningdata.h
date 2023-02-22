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

    void setControlContourAmount(int thrusterAmount);
    int getControlContourAmount();
    UV_ControlContour getControlContourData(STABILIZATION_CONTOURS slot);
    UV_StabilizationState getControlContourStabilizationState(unsigned int slot);
    void setCurrentControlContour(STABILIZATION_CONTOURS contour);
    void setControlContourData(unsigned int slot, UV_ControlContour data);
    void setControlContourData(unsigned int slot, UV_StabilizationConstants data);

    void setStabDepth(bool state);
    void setStabYaw(bool state);

    void setStabPitch(bool state);
};

#endif // ITHRUSTERTUNINGDATA_H
