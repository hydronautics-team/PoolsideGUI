#ifndef UV_STATE_H
#define UV_STATE_H

#include "stdint.h"

#include "uv_device.h"
#include "uv_thrusters.h"

enum e_MessageTypes {
    MESSAGE_NORMAL = 0,
    MESSAGE_CONFIG,
    MESSAGE_DIRECT
};

class UV_State
{
public:
    UV_State();

    const static unsigned int devices_amount = 4;
    const static unsigned int thrusters_amount = 8;

    // Current message type
    int messageType;

    // Control values
    // Linear movement
    double march;
    double lag;
    double depth;
    // Angular movement
    double roll;
    double pitch;
    double yaw;

    // IMU values
    // Angular movement
    double sensors_roll;
    double sensors_pitch;
    double sensors_yaw;
    // Angular speed
    double sensors_rollSpeed;
    double sensors_pitchSpeed;
    double sensors_yawSpeed;
    // Depth
    double sensors_depth;
    double sensors_inpressure;

    // Devices
    UV_device devices[devices_amount];
    // Thrusters
    UV_Thrusters thrusters[thrusters_amount];
    // Stabilization Contours

    uint8_t cameras;
    uint8_t pc_reset;
    uint16_t checksum;

    uint8_t ThrusterSelected;
};

#endif // UV_STATE_H
