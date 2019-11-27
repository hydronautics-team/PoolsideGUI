#ifndef UV_STATE_H
#define UV_STATE_H

#include "stdint.h"

#include "uv_device.h"

enum devices_names {
    BeaconDropper,
    BeaconGetter
};

class UV_State
{
public:
    UV_State();

    const static unsigned int devices_amount = 2;
private:
    // Linear movement
    double march;
    double lag;
    double depth;
    // Angular movement
    double roll;
    double pitch;
    double yaw;
    // Devices
    UV_device *devices;
    // Stabilization Contours


    uint8_t cameras;
    uint8_t pc_reset;
    uint16_t checksum;
};

#endif // UV_STATE_H
