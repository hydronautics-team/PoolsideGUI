#include "ithrustertuningdata.h"

IThrusterTuningData::IThrusterTuningData()
{

}

UV_Thruster IThrusterTuningData::getThrusterData(unsigned int slot)
{
    UV_Thruster data;
    if(slot < UV_State::thrusters_amount) {
        UVMutex.lock();
        data = UVState.thruster[slot];
        UVMutex.unlock();
    }
    else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(UV_State::thrusters_amount) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
    return data;
}

void IThrusterTuningData::setThrusterData(unsigned int slot, UV_Thruster data)
{
    if(slot < UV_State::thrusters_amount) {
        UVMutex.lock();
        UVState.thruster[slot] = data;
        UVMutex.unlock();
    }
    else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(UV_State::thrusters_amount) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
}
