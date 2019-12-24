#include "uv_device.h"

unsigned int UV_device::devices_number = 0;

UV_device::UV_device(std::string dev_name, unsigned int dev_id)
{
    name = dev_name;
    id = dev_id;

    slot = devices_number;
    devices_number++;

    control = 0;
    current = 0;
}
