#ifndef UV_STABILIZATION_H
#define UV_STABILIZATION_H

enum STABILIZATION_CONTOURS {
    CONTOUR_DEPTH = 0,
    CONTOUR_MARCH,
    CONTOUR_LAG,
    CONTOUR_YAW,
    CONTOUR_ROLL,
    CONTOUR_PITCH
};

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

    float thrustersFilterT;
    float thrustersFilterK;

    float sOutSummatorMax;
    float sOutSummatorMin;
};

struct UV_StabilizationState {
    float inputSignal;
    float speedSignal;
    float posSignal;

    float joyUnitCasted;
    float joy_iValue;
    float posError;
    float speedError;
    float dynSummator;
    float pidValue;
    float posErrorAmp;
    float speedFiltered;
    float posFiltered;
    float pid_iValue;
    float thrustersFiltered;

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
