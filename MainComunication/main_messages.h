#ifndef MAINMESSAGES_H
#define MAINMESSAGES_H

#include <stdint.h>
#include <QDataStream>

/// Number of the thrusters
static const uint8_t VmaAmount = 8;

/// Number of the devs
static const uint8_t DevAmount = 6;

uint16_t getChecksum16b(std::vector<char> &msg);

/** \brief Structure for storing and processing data from the STM32 normal request message protocol
 * Normal request message protocol is used for movement and devices control, turning stabilization on and off and onboard pc resets
 * Shore send requests and STM send responses
 */
struct RequestMessage
{
    RequestMessage();

    /// Type code for the normal message protocol
    const static uint8_t type = 0xA5;
    uint8_t flags;
    int16_t march;
    int16_t lag;
    int16_t depth;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    int8_t dev[DevAmount];
    uint8_t dev_flags;
    uint8_t stabilize_flags;
    uint8_t cameras;
    uint8_t pc_reset;
    //uint16_t checksum;

    friend QDataStream& operator<<(QDataStream &ds, const RequestMessage &req)
    {
        ds.setByteOrder(QDataStream::LittleEndian);
        ds.setFloatingPointPrecision(QDataStream::SinglePrecision);
        ds << req.type;
        ds << req.flags;
        ds << req.march;
        ds << req.lag;
        ds << req.depth;
        ds << req.roll;
        ds << req.pitch;
        ds << req.yaw;
        for(int i=0; i<DevAmount; i++) {
            ds << req.dev[i];
        }
        ds << req.dev_flags;
        ds << req.stabilize_flags;
        ds << req.cameras;
        ds << req.pc_reset;
        return ds;
    }
};

/** \brief Structure for storing and processing data from the STM32 normal response message protocol
 * Normal response message contains various telemetry (orientation sensors, current of the thrusters and devices, leak data and internal errors)
 * Shore send requests and STM send responses
 */
struct ResponseMessage
{
    ResponseMessage();

    float roll;
    float pitch;
    float yaw;

    float rollSpeed;
    float pitchSpeed;
    float yawSpeed;

    float depth;
    float in_pressure;

    uint8_t dev_state;
    int16_t leak_data;

    uint16_t vma_current[VmaAmount];
    uint16_t dev_current[DevAmount];

    uint16_t vma_errors;
    uint16_t dev_errors;
    uint8_t pc_errors;

    uint16_t checksum;

    friend QDataStream& operator>>(QDataStream &ds, ResponseMessage &res)
    {
        ds.setByteOrder(QDataStream::LittleEndian);
        ds.setFloatingPointPrecision(QDataStream::SinglePrecision);
        ds >> res.roll;
        ds >> res.pitch;
        ds >> res.yaw;

        ds >> res.rollSpeed;
        ds >> res.pitchSpeed;
        ds >> res.yawSpeed;

        ds >> res.depth;
        ds >> res.in_pressure;

        ds >> res.dev_state;
        ds >> res.leak_data;

        for(int i=0; i<DevAmount; i++) {
            ds >> res.dev_current[i];
        }

        for(int i=0; i<VmaAmount; i++) {
             ds >> res.vma_current[i];
        }

        ds >> res.vma_errors;
        ds >> res.dev_errors;
        ds >> res.pc_errors;

        ds >> res.checksum;
        return ds;
    }
};

/** \brief Structure for storing and processing data from the STM32 configuration request message protocol
 * Configuration request message protocol is used for movement control of the UV and tuning selected stabilization contour
 * Shore send requests and STM send responses
 */
struct RequestConfigMessage
{
    RequestConfigMessage();

    /// Type code for the normal message protocol
    const static uint8_t type = 0x55;

    uint8_t contour;

    int16_t march;
    int16_t lag;
    int16_t depth;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;

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

    uint16_t checksum;

    friend QDataStream& operator<<(QDataStream &ds, const RequestConfigMessage &req)
    {
        ds.setByteOrder(QDataStream::LittleEndian);
        ds.setFloatingPointPrecision(QDataStream::SinglePrecision);
        ds << req.type;
        ds << req.contour;

        ds << req.march;
        ds << req.lag;
        ds << req.depth;
        ds << req.roll;
        ds << req.pitch;
        ds << req.yaw;

        ds << req.pJoyUnitCast;
        ds << req.pSpeedDyn;
        ds << req.pErrGain;

        ds << req.posFilterT;
        ds << req.posFilterK;
        ds << req.speedFilterT;
        ds << req.speedFilterK;

        ds << req.pid_pGain;
        ds << req.pid_iGain;
        ds << req.pid_iMax;
        ds << req.pid_iMin;

        ds << req.pThrustersMin;
        ds << req.pThrustersMax;

        ds << req.thrustersFilterT;
        ds << req.thrustersFilterK;

        ds << req.sOutSummatorMax;
        ds << req.sOutSummatorMin;
        return ds;
    }
};

/** \brief Structure for storing and processing data from the STM32 configuration response message protocol
 * Configuration response message contains orientation sensor information and internal variables of the selected stabilization contour
 * Shore send requests and STM send responses
 */
struct ResponseConfigMessage
{
    ResponseConfigMessage();

    uint8_t code;

    float roll;
    float pitch;
    float yaw;
    float raw_yaw;

    float rollSpeed;
    float pitchSpeed;
    float yawSpeed;

    float pressure;
    float in_pressure;

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

    uint16_t checksum;

    friend QDataStream& operator>>(QDataStream &ds, ResponseConfigMessage &res)
    {
        ds.setByteOrder(QDataStream::LittleEndian);
        ds.setFloatingPointPrecision(QDataStream::SinglePrecision);
        ds >> res.code;

        ds >> res.roll;
        ds >> res.pitch;
        ds >> res.yaw;
        ds >> res.raw_yaw;

        ds >> res.rollSpeed;
        ds >> res.pitchSpeed;
        ds >> res.yawSpeed;

        ds >> res.pressure;
        ds >> res.in_pressure;

        ds >> res.inputSignal;
        ds >> res.speedSignal;
        ds >> res.posSignal;

        ds >> res.joyUnitCasted;
        ds >> res.joy_iValue;
        ds >> res.posError;
        ds >> res.speedError;
        ds >> res.dynSummator;
        ds >> res.pidValue;
        ds >> res.posErrorAmp;
        ds >> res.speedFiltered;
        ds >> res.posFiltered;
        ds >> res.pid_iValue;
        ds >> res.thrustersFiltered;

        ds >> res.outputSignal;

        ds >> res.checksum;
        return ds;
    }
};

/** \brief Structure for storing and processing data from the STM32 direct request message protocol
 * Direcy request message protocol is used for controlling and tuning one particular thruster
 * Shore send requests and STM send responses
 */
struct RequestDirectMessage
{
    RequestDirectMessage();

    /// Type code for the normal message protocol
    const static uint8_t type = 0xAA;

    uint8_t number;
    uint8_t id;

    int8_t velocity;

    uint8_t reverse;
    float kForward;
    float kBackward;

    int8_t sForward;
    int8_t sBackward;

    uint16_t checksum;

    friend QDataStream& operator<<(QDataStream &ds, const RequestDirectMessage &req)
    {
        ds.setByteOrder(QDataStream::LittleEndian);
        ds.setFloatingPointPrecision(QDataStream::SinglePrecision);
        ds << req.type;
        ds << req.number;
        ds << req.id;

        ds << req.velocity;

        ds << req.reverse;
        ds << req.kForward;
        ds << req.kBackward;

        ds << req.sForward;
        ds << req.sBackward;
        return ds;
    }
};

/** \brief Structure for storing and processing data from the STM32 direct response message protocol
 * Direct response message contains current and status information from particular thruster
 * Shore send requests and STM send responses
 */
struct ResponseDirectMessage
{
    ResponseDirectMessage();

    uint8_t number;
    uint8_t connection;
    uint16_t current;

    uint16_t checksum;

    friend QDataStream& operator>>(QDataStream &ds, ResponseDirectMessage &res)
    {
        ds.setByteOrder(QDataStream::LittleEndian);
        ds.setFloatingPointPrecision(QDataStream::SinglePrecision);
        ds >> res.number;
        ds >> res.connection;
        ds >> res.current;

        ds >> res.checksum;
        return ds;
    }
};

#endif // MAINMESSAGES_H
