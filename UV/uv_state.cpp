#include "uv_state.h"

ImuData::ImuData()
{
    roll = 0;
    pitch = 0;
    yaw = 0;
    rollSpeed = 0;
    pitchSpeed = 0;
    yawSpeed = 0;
    depth = 0;
}

ControlData::ControlData()
{
    march = 0;
    lag = 0;
    depth = 0;
    roll = 0;
    pitch = 0;
    yaw = 0;
};

UV_State::UV_State()
{

}
