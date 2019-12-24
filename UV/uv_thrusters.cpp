#include "uv_thrusters.h"

UV_Thrusters::UV_Thrusters()
{
    name = "THRUSTER";

    id = 0;
    slot = 0;

    kForward = 100;
    kBackward = 100;
    sForward = 100;
    sBackward = 100;

    velocity = 0;
}
