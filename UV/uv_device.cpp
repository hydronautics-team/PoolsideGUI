#include "uv_device.h"

unsigned int UV_Device::devices_number = 0;

UV_Device::UV_Device() {
    name = "dev_name";
    id = 0;

    slot = devices_number;
    devices_number++;

    velocity = 0;
    current = 0;
}

UV_Device::UV_Device(QString dev_name, unsigned int dev_id) {
    name = dev_name;
    id = dev_id;

    slot = devices_number;
    devices_number++;

    velocity = 0;
    current = 0;
}
