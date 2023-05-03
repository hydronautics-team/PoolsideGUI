#ifndef UV_STABILIZATION_H
#define UV_STABILIZATION_H

struct UV_StabilizationConstants {
    float pJoyUnitCast;
    float pSpeedDyn;
    float pErrGain;

    float posFilterT;
    float posFilterK;
    float speedFilterT;
    float speedFilterK;

    float pid_pGain;
    float pid_iGain;
    float pid_iMax;
    float pid_iMin;

    float pThrustersMin;
    float pThrustersMax;
    float pThrustersCast;
};

struct UV_StabilizationState {
    float inputSignal;
    float speedSignal;
    float posSignal;

    float joyUnitCasted;
    float posError;
    float joy_iValue;
    float speedError;
    float dynSummator;
    float pidValue;
    float posErrorAmp;
    float speedFiltered;
    float posFiltered;
    float pid_iValue;
    float pid_pValue;
    float outputSignal;
};

/** \brief Base class for stabilization contour of the underwater vehicle
 * UV can receive configuration messages and send back debug informations about contour
 */
class UV_ControlContour {
public:
    UV_ControlContour();

    UV_StabilizationConstants constant;
    UV_StabilizationState state;
};

#endif // UV_STABILIZATION_H
