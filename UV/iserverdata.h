#ifndef ISERVERDATA_H
#define ISERVERDATA_H

#include <QDataStream>
#include <QByteArray>

#include "ibasicdata.h"
#include "uv_state.h"

enum e_messageErrors {
    MESSAGE_ERROR_ID_NOT_FOUND = 0
};

class IServerData : public IBasicData
{
public:
    IServerData(UV_State *target, QMutex *target_mutex);

    QByteArray getMessage(int message_type);
    void passMessage(QByteArray message, int message_type);

private:
    QDataStream *port;

    /// Number of the thrusters
    static const uint8_t VmaAmount = 8;

    /// Number of the devs
    static const uint8_t DevAmount = 6;

    struct RequestNormalMessage
    {
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
        uint16_t checksum;
    };

    /** \brief Structure for storing and processing data from the STM32 normal response message protocol
     * Normal response message contains various telemetry (orientation sensors, current of the thrusters and devices, leak data and internal errors)
     * Shore send requests and STM send responses
     */
    struct ResponseNormalMessage
    {
        float roll;
        float pitch;
        float yaw;

        float rollSpeed;
        float pitchSpeed;
        float yawSpeed;

        float depth;
        float inpressure;

        uint8_t dev_state;
        int16_t leak_data;

        uint16_t vma_current[VmaAmount];
        uint16_t dev_current[DevAmount];

        uint16_t vma_errors;
        uint16_t dev_errors;
        uint8_t pc_errors;

        uint16_t checksum;
    };

    /** \brief Structure for storing and processing data from the STM32 configuration request message protocol
     * Configuration request message protocol is used for movement control of the UV and tuning selected stabilization contour
     * Shore send requests and STM send responses
     */
    struct RequestConfigMessage
    {
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
    };

    /** \brief Structure for storing and processing data from the STM32 configuration response message protocol
     * Configuration response message contains orientation sensor information and internal variables of the selected stabilization contour
     * Shore send requests and STM send responses
     */
    struct ResponseConfigMessage
    {
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
    };

    /** \brief Structure for storing and processing data from the STM32 direct request message protocol
     * Direcy request message protocol is used for controlling and tuning one particular thruster
     * Shore send requests and STM send responses
     */
    struct RequestDirectMessage
    {
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
    };

    /** \brief Structure for storing and processing data from the STM32 direct response message protocol
     * Direct response message contains current and status information from particular thruster
     * Shore send requests and STM send responses
     */
    struct ResponseDirectMessage
    {
        uint8_t number;
        uint8_t connection;
        uint16_t current;

        uint16_t checksum;
    };

    bool parseNormalMessage(QByteArray msg);
    bool parseConfigMessage(QByteArray msg);
    bool parseDirectMessage(QByteArray msg);

    QByteArray formNormalMessage();
    QByteArray formConfigMessage();
    QByteArray formDirectMessage();

    void fill(RequestNormalMessage &req);
    void fill(RequestConfigMessage &req);
    void fill(RequestDirectMessage &req);

    void pull(ResponseNormalMessage res);
    void pull(ResponseConfigMessage res);
    void pull(ResponseDirectMessage res);
};

#endif // ISERVERDATA_H
