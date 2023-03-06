#include "uv_controlcontour.h"

UV_ControlContour::UV_ControlContour() {
    constant.pJoyUnitCast = 0;
    constant.pSpeedDyn = 0;
    constant.pErrGain = 0;

    constant.posFilterT = 0;
    constant.posFilterK = 0;
    constant.speedFilterT = 0;
    constant.speedFilterK = 0;

    constant.pid_pGain = 0;
    constant.pid_iGain = 0;
    constant.pid_iMax = 0;
    constant.pid_iMin = 0;

    constant.pThrustersMin = 0;
    constant.pThrustersMax = 0;
    constant.pThrustersCast = 0;

    state.inputSignal = 0;
    state.speedSignal = 0;
    state.posSignal = 0;

    state.joyUnitCasted = 0;
    state.posError = 0;
    state.joy_iValue = 0;
    state.speedError = 0;
    state.dynSummator = 0;
    state.pidValue = 0;
    state.posErrorAmp = 0;
    state.speedFiltered = 0;
    state.posFiltered = 0;
    state.pid_iValue = 0;
    state.pid_pValue = 0;
    state.outputSignal = 0;
}
