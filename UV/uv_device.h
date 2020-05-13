#ifndef UV_DEVICES_H
#define UV_DEVICES_H

#include <QString>

/** \brief Base class for devices installed on underwater vehicle
 * Usually we can control velocity (voltage) of the device, and receive current from it
 */
class UV_Device
{
public:
    UV_Device();
    UV_Device(QString dev_name, unsigned int dev_id);

    static unsigned int devices_number;

    QString name;
    unsigned int id;
    unsigned int slot;

    double velocity;
    double current;
};

#endif // UV_DEVICES_H
