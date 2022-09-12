#ifndef UV_STATE_H
#define UV_STATE_H

#include "stdint.h"

#include <QDebug>
#include "uv_device.h"
#include "uv_thruster.h"
#include "uv_controlcontour.h"

struct ImuData {
    ImuData();

    double roll;
    double pitch;
    double yaw;
    double rollSpeed;
    double pitchSpeed;
    double yawSpeed;
    double depth;
};

struct ControlData {
    ControlData();

    double march;
    double lag;
    double depth;
    double roll;
    double pitch;
    double yaw;
};

class UV_State {
public:
    UV_State();
    ~UV_State();

    // TODO: Replace this with dynamic arrays (later)
    const static unsigned int devices_amount = 6;

    int thrusterAmount;

    void setThrusterAmount(int thrusterAmount);
    int getThrusterAmount();

    int controlContourAmount;

    void setControlContourAmount(int controlContourAmount);
    int getControlContourAmount();

    // ControlWindow values
    ControlData control;

    // IMU values
    ImuData imu;

    // Auxiliar state values
    double aux_inpressure;

    // Devices
    UV_Device device[devices_amount];

    // Thrusters
    UV_Thruster *thruster;

    // Stabilization Contours
    STABILIZATION_CONTOURS currentControlContour;
    UV_ControlContour *controlContour;

    // Flags
    bool resetImu;
    bool stabYaw;
    bool stabDepth;
};

#endif // UV_STATE_H
