#include "ituningdata.h"

ITuningData::ITuningData() {

}

void ITuningData::setThrusterAmount(int thrusterAmount){
    UVMutex.lock();
    UVState.setThrusterAmount(thrusterAmount);
    UVMutex.unlock();
}

int ITuningData::getThrusterAmount() {
    int thrusterAmount;
    UVMutex.lock();
    thrusterAmount = sizeof(UV_State::thruster);
    UVMutex.unlock();
    return thrusterAmount;
}

UV_Thruster ITuningData::getThrusterData(unsigned int slot) {
    UV_Thruster data;
    if (slot < getThrusterAmount()) {
        UVMutex.lock();
        data = UVState.thruster[slot];
        UVMutex.unlock();
        qDebug() << data.id;
    } else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(getThrusterAmount()) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
    return data;
}

void ITuningData::setThrusterData(unsigned int slot, UV_Thruster data) {
    if (slot < getThrusterAmount()) {
        UVMutex.lock();
        UVState.thruster[slot] = data;
        UVMutex.unlock();
    } else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(getThrusterAmount()) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
}

UV_ControlContour ITuningData::getControlContourData(unsigned int slot) {
    UV_ControlContour data;
    if (slot < UV_State::control_counters_amount) {
        UVMutex.lock();
        data = UVState.ControlContour[slot];
        UVMutex.unlock();
    } else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(UV_State::control_counters_amount) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
    return data;
}

void ITuningData::setControlContourData(unsigned int slot, UV_ControlContour data) {
    if (slot < UV_State::control_counters_amount) {
        UVMutex.lock();
        UVState.ControlContour[slot] = data;
        UVMutex.unlock();
    } else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(UV_State::control_counters_amount) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
}
