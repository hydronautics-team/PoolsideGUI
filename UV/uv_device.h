#ifndef UV_DEVICES_H
#define UV_DEVICES_H

#include <string>

class UV_device
{
public:
    UV_device(std::string dev_name, unsigned int dev_id);

    float getControl() const;
    void setControl(float value);

    float getCurrent() const;

    // Number of initialized devices
    static unsigned int devices_number;

private:

protected:
    std::string name;
    unsigned int id;
    unsigned int slot;

    float control;
    float current;
};

#endif // UV_DEVICES_H
