#ifndef UV_STATE_H
#define UV_STATE_H

#include "stdint.h"

#include <QDebug>
#include "uv_device.h"
#include "uv_thruster.h"
#include "uv_controlcontour.h"

enum e_packageMode {
    PACKAGE_NORMAL,
    PACKAGE_CONFIG,
    PACKAGE_DIRECT,
};

enum e_Countour {
    CONTOUR_DEPTH,
    CONTOUR_MARCH,
    CONTOUR_LAG,
    CONTOUR_YAW,
    CONTOUR_ROLL,
    CONTOUR_PITCH,
};

enum e_Connection {
    CONNECTION_UDP,
    CONNECTION_SERIAL,
};

enum e_Device {
    DEVICE_GRAB,
    DEVICE_GRAB_ROTATE,
    DEVICE_TILT,
    DEVICE_DEV1,
    DEVICE_DEV2,
    DEVICE_DEV3
};

struct ImuData {
    ImuData();

    double roll;
    double pitch;
    double yaw;
    double rollSpeed;
    double pitchSpeed;
    double yawSpeed;
    double depth;
};

struct ControlData {
    ControlData();

    int16_t march;
    int16_t lag;
    int16_t depth;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
};

class UV_State {
public:
    UV_State();
    ~UV_State();

    int thrusterAmount;
    void setThrusterNext();
    void setThrusterAmount(int thrusterAmount);
    int getThrusterAmount();

    ControlData control;
    ImuData imu;

    UV_Device device[6];
    UV_Thruster* thruster;
    int currentThruster;
    UV_ControlContour controlContour[6];
    e_Countour currentControlContour;

    e_Connection currentConnectionMode;
    e_packageMode currentPackageMode;

    // Flags
    bool stabRoll;
    bool stabYaw;
    bool stabPitch;
    bool stabDepth;

    bool resetImu;
    bool thrustersON;
};

#endif // UV_STATE_H
