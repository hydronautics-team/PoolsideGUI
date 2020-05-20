#include "ituningdata.h"

ITuningData::ITuningData()
{

}

UV_Thruster ITuningData::getThrusterData(unsigned int slot)
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

void ITuningData::setThrusterData(unsigned int slot, UV_Thruster data)
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

UV_ControlContour ITuningData::getControlContourData(unsigned int slot)
{
    UV_ControlContour data;
    if(slot < UV_State::control_counters_amount) {
        UVMutex.lock();
        data = UVState.ControlContour[slot];
        UVMutex.unlock();
    }
    else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(UV_State::control_counters_amount) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
    return data;
}

void ITuningData::setControlContourData(unsigned int slot, UV_ControlContour data)
{
    if(slot < UV_State::control_counters_amount) {
        UVMutex.lock();
        UVState.ControlContour[slot] = data;
        UVMutex.unlock();
    }
    else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(UV_State::control_counters_amount) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
}
