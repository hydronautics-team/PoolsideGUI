#include "ituningdata.h"

ITuningData::ITuningData() {
}

void ITuningData::setThrusterAmount(int thrusterAmount) {
    UVMutex.lock();
    UVState.setThrusterAmount(thrusterAmount);
    UVMutex.unlock();
}

int ITuningData::getThrusterAmount() {
    int thrusterAmount;
    UVMutex.lock();
    thrusterAmount = UVState.getThrusterAmount();
    UVMutex.unlock();
    return thrusterAmount;
}

void ITuningData::setThrusterData(int slot, UV_Thruster data) {
    if (slot < UVState.getThrusterAmount()) {
        UVMutex.lock();
        UVState.thruster[slot] = data;
        UVMutex.unlock();
    } else {
        std::string error = "Max thruster slot is: " +
            std::to_string(UVState.getThrusterAmount()) +
            ", you are trying to reach:" +
            std::to_string(slot);
        throw std::invalid_argument(error);
    }
}

UV_Thruster ITuningData::getThrusterData(int slot) {
    UV_Thruster data;
    if (slot < getThrusterAmount()) {
        UVMutex.lock();
        data = UVState.thruster[slot];
        UVMutex.unlock();
    } else {
        std::string error = "Max thruster slot is: " +
            std::to_string(UVState.getThrusterAmount()) +
            ", you are trying to reach:" +
            std::to_string(slot);
        throw std::invalid_argument(error);
    }
    return data;
}

void ITuningData::setThrusterPower(int slot, bool power) {
    if (slot < getThrusterAmount()) {
        UVMutex.lock();
        UVState.thruster[slot].power = power;
        UVMutex.unlock();
    } else {
        std::string error = "Max thruster slot is: " +
            std::to_string(UVState.getThrusterAmount()) +
            ", you are trying to reach:" +
            std::to_string(slot);
        throw std::invalid_argument(error);
    }
}

UV_StabilizationState ITuningData::getControlContourState(e_Countour countour) {
    UV_StabilizationState data;
    UVMutex.lock();
    data = UVState.controlContour[countour].state;
    UVMutex.unlock();
    return data;
}

void ITuningData::setControlContourConstants(UV_StabilizationConstants constants) {
    UVMutex.lock();
    UVState.controlContour[UVState.currentControlContour].constant = constants;
    UVMutex.unlock();
}

void ITuningData::setControlContourConstants(UV_StabilizationConstants constants, e_Countour countour) {
    UVMutex.lock();
    UVState.controlContour[countour].constant = constants;
    UVMutex.unlock();
}

void ITuningData::setCurrentControlContour(e_Countour contour) {
    UVMutex.lock();
    UVState.currentControlContour = contour;
    UVMutex.unlock();

}
