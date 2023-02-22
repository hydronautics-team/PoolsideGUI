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
    thrusterAmount = UVState.getThrusterAmount();
    UVMutex.unlock();
    return thrusterAmount;
}

UV_Thruster ITuningData::getThrusterData(unsigned int slot) {
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

void ITuningData::setThrusterData(unsigned int slot, UV_Thruster data) {
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

void ITuningData::setControlContourAmount(int controlContourAmount){
    UVMutex.lock();
    UVState.setControlContourAmount(controlContourAmount);
    UVMutex.unlock();
}

int ITuningData::getControlContourAmount() {
    int controlContourAmount;
    UVMutex.lock();
    controlContourAmount = UVState.getControlContourAmount();
    UVMutex.unlock();
    return controlContourAmount;
}

UV_ControlContour ITuningData::getControlContourData(STABILIZATION_CONTOURS slot) {
    UV_ControlContour data;
    if (slot < UVState.getControlContourAmount()) {
        UVMutex.lock();
        data = UVState.controlContour[slot];
        UVMutex.unlock();
    } else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(UVState.getControlContourAmount()) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
    return data;
}

void ITuningData::setCurrentControlContour(STABILIZATION_CONTOURS contour) {
    UVMutex.lock();
    UVState.currentControlContour = contour;
    UVMutex.unlock();
    qDebug() << "setCurrentControlContour to " << contour;
}

void ITuningData::setControlContourData(unsigned int slot, UV_ControlContour data) {
    if (slot < UVState.getControlContourAmount()) {
        UVMutex.lock();
        UVState.controlContour[slot] = data;
        UVMutex.unlock();
    } else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(UVState.getControlContourAmount()) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
}

void ITuningData::setControlContourData(unsigned int slot, UV_StabilizationConstants data) {
    if (slot < UVState.getControlContourAmount()) {
        UVMutex.lock();
        UVState.controlContour[slot].constant = data;
        UVMutex.unlock();
    } else {
        std::string error = "Max thruster slot is: " +
                            std::to_string(UVState.getControlContourAmount()) +
                            ", you are trying to reach:" +
                            std::to_string(slot);
        throw std::invalid_argument(error);
    }
}

void ITuningData::setStabDepth(bool state) {
    UVMutex.lock();
    UVState.stabDepth = state;
    UVMutex.unlock();
}

void ITuningData::setStabYaw(bool state) {
    UVMutex.lock();
    UVState.stabYaw = state;
    UVMutex.unlock();
}

void ITuningData::setStabPitch(bool state) {
    UVMutex.lock();
    UVState.stabPitch = state;
    UVMutex.unlock();
}
