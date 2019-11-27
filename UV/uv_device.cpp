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

float UV_device::getControl() const
{
    return control;
}

void UV_device::setControl(float value)
{
    control = value;
}

float UV_device::getCurrent() const
{
    return current;
}
