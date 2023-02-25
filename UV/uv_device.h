#ifndef UV_DEVICES_H
#define UV_DEVICES_H

#include <QString>

/** \brief Base class for devices installed on underwater vehicle
 * Usually we can control velocity (voltage) of the device, and receive current from it
 */
class UV_Device {
public:
    UV_Device();

    double velocity;
};

#endif // UV_DEVICES_H
