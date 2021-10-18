#ifndef UV_STATE_H
#define UV_STATE_H

#include "stdint.h"

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

    // TODO: Replace this with dynamic arrays (later)
    const static unsigned int devices_amount = 6;
    const static unsigned int thrusters_amount = 8;
    const static unsigned int control_counters_amount = 6;

    // ControlWindow values
    ControlData control;

    // IMU values
    ImuData imu;

    // Auxiliar state values
    double aux_inpressure;

    // Devices
    UV_Device device[devices_amount];

    // Thrusters
    UV_Thruster thruster[thrusters_amount];

    // Stabilization Contours
    UV_ControlContour ControlContour[control_counters_amount];

    // Flags
    bool resetImu;
};

#endif // UV_STATE_H
