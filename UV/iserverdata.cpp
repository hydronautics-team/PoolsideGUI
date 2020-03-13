#include "iserverdata.h"

#include "rovmodewidget.h"

int16_t resizeDoubleToInt16(double input, double border);
int8_t resizeDoubleToInt8(double input, double border);

uint16_t getCheckSumm16b(char *pcBlock, int len);
uint8_t isCheckSumm16bCorrect(char *pcBlock, int len);
void addCheckSumm16b(char *pcBlock, int len);

IServerData::IServerData(UV_State *target, QMutex *target_mutex)
    : IBasicData(target, target_mutex)
{

}

QByteArray IServerData::getMessage(int message_type)
{
    QByteArray formed;
    formed.clear();
    getData();
    switch(message_type) {
        case MESSAGE_NORMAL:
            formed = formNormalMessage();
            break;
        case MESSAGE_CONFIG:
            formed = formConfigMessage();
            break;
        case MESSAGE_DIRECT:
            formed = formDirectMessage();
            break;
    }
    return formed;
}

void IServerData::passMessage(QByteArray message, int message_type)
{
    switch(message_type) {
        case MESSAGE_NORMAL:
            parseNormalMessage(message);
            break;
        case MESSAGE_CONFIG:
            parseConfigMessage(message);
            break;
        case MESSAGE_DIRECT:
            parseDirectMessage(message);
            break;
    }

    UV_State *ptr = gainAccess();
    ptr->sensors_roll = internal_state.sensors_roll;
    ptr->sensors_pitch = internal_state.sensors_pitch;
    ptr->sensors_yaw = internal_state.sensors_yaw;
    // Angular speed
    ptr->sensors_rollSpeed = internal_state.sensors_rollSpeed;
    ptr->sensors_pitchSpeed = internal_state.sensors_pitchSpeed;
    ptr->sensors_yawSpeed = internal_state.sensors_yawSpeed;
    // Depth
    ptr->sensors_depth = internal_state.sensors_depth;
    ptr->sensors_inpressure = internal_state.sensors_inpressure;
    closeAccess();
}

bool IServerData::parseNormalMessage(QByteArray msg)
{
    ResponseNormalMessage res;

    uint16_t checksum_calc = getCheckSumm16b(msg.data(), msg.size()-2);

    QDataStream stream(&msg, QIODevice::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    stream >> res.roll;
    stream >> res.pitch;
    stream >> res.yaw;

    stream >> res.rollSpeed;
    stream >> res.pitchSpeed;
    stream >> res.yawSpeed;

    stream >> res.depth;
    stream >> res.inpressure;

    stream >> res.dev_state;
    stream >> res.leak_data;

    for(int i=0; i<VmaAmount; i++) {
        stream >> res.vma_current[i];
    }

    for(int i=0; i<DevAmount; i++) {
        stream >> res.dev_current[i];
    }

    stream >> res.vma_errors;
    stream >> res.dev_errors;
    stream >> res.pc_errors;

    stream >> res.checksum;

    if(res.checksum != checksum_calc) {
        //return false;
    }

    pull(res);
    return true;
}

bool IServerData::parseConfigMessage(QByteArray msg)
{
    ResponseConfigMessage res;

    uint16_t checksum_calc = getCheckSumm16b(msg.data(), msg.size()-2);

    QDataStream stream(&msg, QIODevice::ReadOnly);

    stream >> res.code;

    stream >> res.roll;
    stream >> res.pitch;
    stream >> res.yaw;
    stream >> res.raw_yaw;

    stream >> res.rollSpeed;
    stream >> res.pitchSpeed;
    stream >> res.yawSpeed;

    stream >> res.pressure;
    stream >> res.in_pressure;

    stream >> res.inputSignal;
    stream >> res.speedSignal;
    stream >> res.posSignal;

    stream >> res.joyUnitCasted;
    stream >> res.joy_iValue;
    stream >> res.posError;
    stream >> res.speedError;
    stream >> res.dynSummator;
    stream >> res.pidValue;
    stream >> res.posErrorAmp;
    stream >> res.speedFiltered;
    stream >> res.posFiltered;
    stream >> res.pid_iValue;
    stream >> res.thrustersFiltered;
    stream >> res.outputSignal;

    stream >> res.checksum;

    if(res.checksum != checksum_calc) {
        return false;
    }

    pull(res);
    return true;
}

bool IServerData::parseDirectMessage(QByteArray msg)
{
    ResponseDirectMessage res;

    uint16_t checksum_calc = getCheckSumm16b(msg.data(), msg.size()-2);

    QDataStream stream(&msg, QIODevice::ReadOnly);

    stream >> res.number;
    stream >> res.connection;
    stream >> res.current;

    stream >> res.checksum;

    if(res.checksum != checksum_calc) {
        return false;
    }

    pull(res);
    return true;
}

QByteArray IServerData::formNormalMessage()
{
    QByteArray msg;
    msg.clear();
    QDataStream stream(&msg, QIODevice::Append);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RequestNormalMessage req;
    fill(req);

    stream << req.type;
    stream << req.flags;
    stream << req.march;
    stream << req.lag;
    stream << req.depth;
    stream << req.roll;
    stream << req.pitch;
    stream << req.yaw;
    for(int i=0; i<DevAmount; i++) {
        stream << req.dev[i];
    }

    stream << req.lag_error;
    stream << req.dev_flags;
    stream << req.stabilize_flags;
    stream << req.cameras;
    stream << req.pc_reset;

    uint16_t checksum = getCheckSumm16b(msg.data(), msg.size());
    stream << checksum;

    return msg;
}

QByteArray IServerData::formConfigMessage()
{
    QByteArray msg;
    msg.clear();
    QDataStream stream(&msg, QIODevice::Append);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RequestConfigMessage req;
    fill(req);

    stream << req.type;
    stream << req.contour;
    stream << req.march;
    stream << req.lag;
    stream << req.depth;
    stream << req.roll;
    stream << req.pitch;
    stream << req.yaw;

    stream << req.pJoyUnitCast;
    stream << req.pSpeedDyn;
    stream << req.pErrGain;

    stream << req.posFilterT;
    stream << req.posFilterK;
    stream << req.speedFilterT;
    stream << req.speedFilterK;

    stream << req.pid_pGain;
    stream << req.pid_iGain;
    stream << req.pid_iMax;
    stream << req.pid_iMin;

    stream << req.pThrustersMin;
    stream << req.pThrustersMax;

    stream << req.thrustersFilterT;
    stream << req.thrustersFilterK;

    stream << req.sOutSummatorMax;
    stream << req.sOutSummatorMin;

    uint16_t checksum = getCheckSumm16b(msg.data(), msg.size());
    stream << checksum;

    return msg;
}

QByteArray IServerData::formDirectMessage()
{ 
    QByteArray msg;
    msg.clear();
    QDataStream stream(&msg, QIODevice::Append);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RequestDirectMessage req;
    fill(req);

    stream << req.type;
    stream << req.number;
    stream << req.id;
    stream << req.velocity;
    stream << req.reverse;
    stream << req.kForward;
    stream << req.kBackward;
    stream << req.sForward;
    stream << req.sBackward;

    uint16_t checksum = getCheckSumm16b(msg.data(), msg.size());
    stream << checksum;

    return msg;
}

void IServerData::fill(RequestNormalMessage &req)
{
    req.flags = 0;
    req.march = resizeDoubleToInt16(internal_state.march, 10);
    req.lag = resizeDoubleToInt16(internal_state.lag, 10);
    req.depth = resizeDoubleToInt16(internal_state.depth, 10);
    req.roll = resizeDoubleToInt16(internal_state.roll, 10);
    req.pitch = resizeDoubleToInt16(internal_state.pitch, 10);
    req.yaw = resizeDoubleToInt16(internal_state.yaw, 10);
    for(int i=0; i<DevAmount; i++) {
        req.dev[i] = resizeDoubleToInt8(internal_state.devices[i].control, 10);
    }

    req.dev_flags = 0;
    req.stabilize_flags = 0;
    req.cameras = 0;
    req.pc_reset = 0;
}

void IServerData::pull(ResponseNormalMessage res)
{
    internal_state.sensors_roll = static_cast<double>(res.roll);
    internal_state.sensors_pitch = static_cast<double>(res.pitch);
    internal_state.sensors_yaw = static_cast<double>(res.yaw);

    internal_state.sensors_rollSpeed = static_cast<double>(res.rollSpeed);
    internal_state.sensors_pitchSpeed = static_cast<double>(res.pitchSpeed);
    internal_state.sensors_yawSpeed = static_cast<double>(res.yawSpeed);

    internal_state.sensors_depth = static_cast<double>(res.depth);
    internal_state.sensors_inpressure = static_cast<double>(res.inpressure);

    /*
    uint8_t dev_state;
    int16_t leak_data;

    uint16_t vma_current[VmaAmount];
    uint16_t dev_current[DevAmount];

    uint16_t vma_errors;
    uint16_t dev_errors;
    uint8_t pc_errors;
    */
}

void IServerData::fill(RequestConfigMessage &req)
{
    req.lag = 0;
}

void IServerData::pull(ResponseConfigMessage res)
{
    res.yaw = 0;
}

void IServerData::fill(RequestDirectMessage &req)
{
    req.number = internal_state.ThrusterSelected;
    req.id = static_cast<uint8_t>(internal_state.thrusters[req.number].id);

    req.velocity = static_cast<int8_t>(internal_state.thrusters[req.number].velocity);

    req.reverse = internal_state.thrusters[req.number].reverse;

    req.kForward = 1;
    req.kBackward = 1;

    req.sForward = static_cast<int8_t>(internal_state.thrusters[req.number].sForward);
    req.sBackward = static_cast<int8_t>(internal_state.thrusters[req.number].sBackward);
}

void IServerData::pull(ResponseDirectMessage res)
{
//    res.number;
//    res.connection;
//    res.current;
}

int16_t resizeDoubleToInt16(double input, double border)
{
    int16_t output = 0;
    double k = 32767/border;
    output = static_cast<int16_t>(input*k);
    return output;
}

int8_t resizeDoubleToInt8(double input, double border)
{
    int16_t output = 0;
    double k = 255/border;
    output = static_cast<int8_t>(input*k);
    return output;
}

/* CRC16-CCITT algorithm */
uint16_t getCheckSumm16b(char *pcBlock, int len)
{
    uint16_t crc = 0xFFFF;
    //int crc_fix = reinterpret_cast<int*>(&crc);
    uint8_t i;

    while (len--) {
        crc ^= *pcBlock++ << 8;

        for (i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

uint8_t isCheckSumm16bCorrect(char *pcBlock, int len)
{
    uint16_t crc_calculated = getCheckSumm16b(pcBlock, len);

    uint16_t *crc_pointer = reinterpret_cast<uint16_t*>(&pcBlock[len-2]);
    uint16_t crc_got = *crc_pointer;

    if(crc_got == crc_calculated) {
        return true;
    }
    else {
        return false;
    }
}

void addCheckSumm16b(char *pcBlock, int len)
{
    uint16_t crc = getCheckSumm16b(pcBlock, len);
    uint16_t *crc_pointer = reinterpret_cast<uint16_t*>(&pcBlock[len-2]);
    *crc_pointer = crc;
}


