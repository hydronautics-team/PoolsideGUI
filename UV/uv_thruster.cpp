#include "uv_thruster.h"

UV_Thruster::UV_Thruster() {
    name = "THRUSTER";

    id = 0;
    slot = 0;

    velocity = 0;

    reverse = false;
    kForward = 1;
    kBackward = 1;

    sForward = 100;
    sBackward = 100;
}
