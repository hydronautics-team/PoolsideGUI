#ifndef ISERVERDATA_H
#define ISERVERDATA_H

#include <QDataStream>
#include <QByteArray>

#include "ibasicdata.h"
#include "uv_state.h"

/** \brief Interface for accessing data in UV_State to form QByteArray messages
 *
 */
class IServerData: public IBasicData {
public:
    IServerData();

    QByteArray generateMessage(e_packageMode packageMode);
    void parseMessage(QByteArray message, e_packageMode packageMode);

    void setCurrentThruster(int id);
    int getThrusterAmount();
    int getCurrentThruster();

    e_Countour getCurrentControlContour();

private:
    QDataStream* port;
    int currentThruster = 0;
    e_Countour currentControlContour = e_Countour(0);

    /** \brief Structure for storing and processing data from the STM32 normal request message protocol
     * Normal request message contains vehicle movement control data, devices control values and various flags
     * Shore send requests and STM send responses
     */
    struct RequestNormalMessage {
        /// Type code for the normal message protocol
        const static uint8_t type = 0xA5;
        uint8_t flags; //stabilize_flags, thrusters_on, reset_imu
        int16_t march;
        int16_t lag;
        int16_t depth;
        int16_t roll;
        int16_t pitch;
        int16_t yaw;

        int8_t dev[6];
        uint16_t checksum;
    };

    /** \brief Structure for storing and processing data from the STM32 normal response message protocol
     * Normal response message contains various telemetry (orientation sensors, current of the thrusters and devices, leak data and internal errors)
     * Shore send requests and STM send responses
     */
    struct ResponseNormalMessage {
        float roll;
        float pitch;
        float yaw;
        float depth;

        float rollSpeed;
        float pitchSpeed;
        float yawSpeed;

        uint16_t checksum;
    };

    /** \brief Structure for storing and processing data from the STM32 configuration request message protocol
     * Configuration request message protocol is used for movement control of the UV and tuning selected stabilization contour
     * Shore send requests and STM send responses
     */
    struct RequestConfigMessage {
        /// Type code for the Config message protocol
        const static uint8_t type = 0x55;
        uint8_t flags; //stabilize_flags, thrusters_on, reset_imu

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
    struct ResponseConfigMessage {
        float roll;
        float pitch;
        float yaw;
        float depth;

        float rollSpeed;
        float pitchSpeed;
        float yawSpeed;

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
    struct RequestDirectMessage {
        /// Type code for the Direct message protocol
        const static uint8_t type = 0xAA;

        uint8_t id;
        uint8_t slot;

        int8_t velocity;

        uint8_t reverse;
        int8_t kForward;
        int8_t kBackward;

        int8_t sForward;
        int8_t sBackward;

        uint16_t checksum;
    };

    /** \brief Structure for storing and processing data from the STM32 direct response message protocol
     * Direct response message contains current and status information from particular thruster
     * Shore send requests and STM send responses
     */
    struct ResponseDirectMessage {
        uint8_t id;

        uint16_t checksum;
    };

    void parseNormalMessage(QByteArray msg);
    void parseConfigMessage(QByteArray msg);
    void parseDirectMessage(QByteArray msg);

    QByteArray generateNormalMessage();
    QByteArray generateConfigMessage();
    QByteArray generateDirectMessage();

    void fillStructure(RequestNormalMessage& req);
    void fillStructure(RequestConfigMessage& req);
    void fillStructure(RequestDirectMessage& req);

    void pullFromStructure(ResponseNormalMessage res);
    void pullFromStructure(ResponseConfigMessage res);
    void pullFromStructure(ResponseDirectMessage res);
};

#endif // ISERVERDATA_H
