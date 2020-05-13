#include "uv_thruster.h"

UV_Thruster::UV_Thruster()
{
    name = "THRUSTER";

    id = 0;
    slot = 0;

    kForward = 100;
    kBackward = 100;
    sForward = 100;
    sBackward = 100;

    velocity = 0;
    current = 0;
}
