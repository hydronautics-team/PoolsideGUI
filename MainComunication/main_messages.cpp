#include "main_messages.h"

/** \brief Constructor for RequestMessage
  *
  */
RequestMessage::RequestMessage()
{
    flags = 0;
    march = 0;
    lag = 0;
    depth = 0;
    roll = 0;
    pitch = 0;
    yaw = 0;

    for(int i=0; i<DevAmount; i++) {
        dev[i] = 0;
    }

    dev_flags = 0;
    stabilize_flags = 0;
    cameras = 0;
    pc_reset = 0;
}

/** \brief Constructor for ResponseMessage
  *
  */
ResponseMessage::ResponseMessage()
{
    roll = 0;
    pitch = 0;
    yaw = 0;

    rollSpeed = 0;
    pitchSpeed = 0;
    yawSpeed = 0;

    depth = 0;
    in_pressure = 0;

    dev_state = 0;
    leak_data = 0;

    for(int i=0; i<VmaAmount; i++) {
        vma_current[i] = 0;
    }

    for(int i=0; i<DevAmount; i++) {
        dev_current[i] = 0;
    }

    vma_errors = 0;
    dev_errors = 0;
    pc_errors = 0;

    checksum = 0;
}

/** \brief Constructor for RequestConfigMessage
  *
  */
RequestConfigMessage::RequestConfigMessage()
{
    contour = 0;

    march = 0;
    lag = 0;
    depth = 0;
    roll = 0;
    pitch = 0;
    yaw = 0;

    pJoyUnitCast = 0;
    pSpeedDyn = 0;
    pErrGain = 0;

    posFilterT = 0;
    posFilterK = 0;
    speedFilterT = 0;
    speedFilterK = 0;

    pid_pGain = 0;
    pid_iGain = 0;
    pid_iMax = 0;
    pid_iMin = 0;

    pThrustersMin = 0;
    pThrustersMax = 0;

    thrustersFilterT = 0;
    thrustersFilterK = 0;

    sOutSummatorMax = 0;
    sOutSummatorMin = 0;

    checksum = 0;
}

/** \brief Constructor for ResponseConfigMessage
  *
  */
ResponseConfigMessage::ResponseConfigMessage()
{
    code = 0;

    roll = 0;
    pitch = 0;
    yaw = 0;
    raw_yaw = 0;

    rollSpeed = 0;
    pitchSpeed = 0;
    yawSpeed = 0;

    pressure = 0;
    in_pressure = 0;

    inputSignal = 0;
    speedSignal = 0;
    posSignal = 0;

    joyUnitCasted = 0;
    joy_iValue = 0;
    posError = 0;
    speedError = 0;
    dynSummator = 0;
    pidValue = 0;
    posErrorAmp = 0;
    speedFiltered = 0;
    posFiltered = 0;
    pid_iValue = 0;
    thrustersFiltered = 0;

    outputSignal = 0;

    checksum = 0;
}

/** \brief Constructor for RequestDirectMessage
  *
  */
RequestDirectMessage::RequestDirectMessage()
{
    number = 0;
    id = 0;

    velocity = 0;

    reverse = 0;
    kForward = 0;
    kBackward = 0;

    sForward = 0;
    sBackward = 0;

    checksum = 0;
}

/** \brief Constructor for ResponseDirectMessage
  *
  */
ResponseDirectMessage::ResponseDirectMessage()
{
    number = 0;
    connection = 0;
    current = 0;

    checksum = 0;
}

/** \brief Gets 16 bit checksum for the content of the stream
  *
  * \param[in]  &msg    Link to the stream
  * \param[in]  length  Length of the message in the stream
  */
uint16_t getChecksum16b(std::vector<char> &vector)
{
    size_t len = vector.size();
    uint16_t crc = 0xFFFF;
    uint8_t i = 0;
    uint8_t g = 0;

    while (len--) {
        crc ^= vector[g++] << 8;

        for (i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

