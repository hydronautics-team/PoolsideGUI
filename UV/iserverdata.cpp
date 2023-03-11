#include "iserverdata.h"

#include <QDebug>
#include <string>
#include <sstream>

uint16_t getCheckSumm16b(char* pcBlock, int len);
uint8_t isCheckSumm16bCorrect(char* pcBlock, int len);

void set_bit(uint8_t& byte, uint8_t bit, bool state);

IServerData::IServerData()
    : IBasicData() {
}

int IServerData::getThrusterAmount() {
    int thrusterAmount;
    UVMutex.lock();
    thrusterAmount = UVState.getThrusterAmount();
    UVMutex.unlock();
    return thrusterAmount;
}

QString IServerData::getUdpHostAddress() {
    QString udpHostAddress;
    UVMutex.lock();
    udpHostAddress = UVState.udpHostAddress;
    UVMutex.unlock();
    return udpHostAddress;
}

quint16 IServerData::getUdpHostPort() {
    quint16 udpHostPort;
    UVMutex.lock();
    udpHostPort = UVState.udpHostPort;
    UVMutex.unlock();
    return udpHostPort;
}

e_Countour IServerData::getCurrentControlContour() {
    e_Countour currentControlContour;

    UVMutex.lock();
    currentControlContour = UVState.currentControlContour;
    UVMutex.unlock();

    return currentControlContour;
}

QByteArray IServerData::generateMessage() {
    QByteArray formed;
    formed.clear();
    switch (getCurrentPackageMode()) {
    case PACKAGE_NORMAL:
        formed = generateNormalMessage();
        break;
    case PACKAGE_CONFIG:
        formed = generateConfigMessage();
        break;
    case PACKAGE_DIRECT:
        formed = generateDirectMessage();
        break;
    }
    return formed;
}

e_packageMode IServerData::getCurrentPackageMode() {
    e_packageMode currentPackageMode;
    UVMutex.lock();
    currentPackageMode = UVState.currentPackageMode;
    UVMutex.unlock();
    return currentPackageMode;
}

QByteArray IServerData::generateNormalMessage() {
    QByteArray msg;
    msg.clear();
    QDataStream stream(&msg, QIODeviceBase::Append);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RequestNormalMessage req;
    fillStructure(req);

    stream << req.type;
    stream << req.flags;
    stream << req.march;
    stream << req.lag;
    stream << req.depth;
    stream << req.roll;
    stream << req.pitch;
    stream << req.yaw;
    for (int i = 0; i < 6; i++) {
        stream << req.dev[i];
    }

    uint16_t checksum = getCheckSumm16b(msg.data(), msg.size());
    stream << checksum;
    return msg;
}

void IServerData::fillStructure(RequestNormalMessage& req) {
    UVMutex.lock();

    set_bit(req.flags, 0, UVState.stabRoll);
    set_bit(req.flags, 1, UVState.stabYaw);
    set_bit(req.flags, 2, UVState.stabPitch);
    set_bit(req.flags, 3, UVState.stabDepth);
    set_bit(req.flags, 4, UVState.resetImu);
    set_bit(req.flags, 5, UVState.thrustersON);

    req.march = UVState.control.march;
    req.lag = UVState.control.lag;
    req.depth = UVState.control.depth;
    req.roll = UVState.control.roll;
    req.pitch = UVState.control.pitch;
    req.yaw = UVState.control.yaw;

    for (int i = 0; i < 6; i++) {
        req.dev[i] = UVState.device[i].velocity;
    }

    UVMutex.unlock();
}

QByteArray IServerData::generateConfigMessage() {
    QByteArray msg;
    msg.clear();
    QDataStream stream(&msg, QIODeviceBase::Append);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RequestConfigMessage req;
    fillStructure(req);

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

    uint16_t checksum = getCheckSumm16b(msg.data(), msg.size());
    stream << checksum;

    return msg;
}

void IServerData::fillStructure(RequestConfigMessage& req) {
    UVMutex.lock();
    e_Countour currentControlContour = UVState.currentControlContour;

    req.march = UVState.control.march;
    req.lag = UVState.control.lag;
    req.depth = UVState.control.depth;
    req.roll = UVState.control.roll;
    req.pitch = UVState.control.pitch;
    req.yaw = UVState.control.yaw;

    req.pJoyUnitCast = UVState.controlContour[currentControlContour].constant.pJoyUnitCast;
    req.pSpeedDyn = UVState.controlContour[currentControlContour].constant.pSpeedDyn;
    req.pErrGain = UVState.controlContour[currentControlContour].constant.pErrGain;
    req.posFilterT = UVState.controlContour[currentControlContour].constant.posFilterT;
    req.posFilterK = UVState.controlContour[currentControlContour].constant.posFilterK;
    req.speedFilterT = UVState.controlContour[currentControlContour].constant.speedFilterT;
    req.speedFilterK = UVState.controlContour[currentControlContour].constant.speedFilterK;
    req.pid_pGain = UVState.controlContour[currentControlContour].constant.pid_pGain;
    req.pid_iGain = UVState.controlContour[currentControlContour].constant.pid_iGain;
    req.pid_iMax = UVState.controlContour[currentControlContour].constant.pid_iMax;
    req.pid_iMin = UVState.controlContour[currentControlContour].constant.pid_iMin;
    req.pThrustersMin = UVState.controlContour[currentControlContour].constant.pThrustersMin;
    req.pThrustersMax = UVState.controlContour[currentControlContour].constant.pThrustersMax;

    UVMutex.unlock();
}

QByteArray IServerData::generateDirectMessage() {
    QByteArray msg;
    msg.clear();
    QDataStream stream(&msg, QIODeviceBase::Append);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RequestDirectMessage req;
    fillStructure(req);

    stream << req.type;
    stream << req.id;
    stream << req.adress;
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

void IServerData::fillStructure(RequestDirectMessage& req) {
    UVMutex.lock();
    UVState.setThrusterNext();

    req.id = UVState.currentThruster;
    req.adress = UVState.thruster[UVState.currentThruster].adress;

    if (UVState.thruster[UVState.currentThruster].power == false) {
        req.velocity = 0;
    } else {
        req.velocity = UVState.thruster[UVState.currentThruster].velocity;
    }

    req.reverse = UVState.thruster[UVState.currentThruster].reverse;
    req.kForward = UVState.thruster[UVState.currentThruster].kForward;
    req.kBackward = UVState.thruster[UVState.currentThruster].kBackward;

    req.sForward = UVState.thruster[UVState.currentThruster].sForward;
    req.sBackward = UVState.thruster[UVState.currentThruster].sBackward;

    UVMutex.unlock();
}

void IServerData::parseMessage(QByteArray message) {
    switch (getCurrentPackageMode()) {
    case PACKAGE_NORMAL:
        parseNormalMessage(message);
        break;
    case PACKAGE_CONFIG:
        parseConfigMessage(message);
        break;
    case PACKAGE_DIRECT:
        parseDirectMessage(message);
        break;
    default:
        throw std::invalid_argument("invalid PackageMode");
    }
}

void IServerData::parseNormalMessage(QByteArray msg) {
    ResponseNormalMessage res;
    uint16_t checksum_calc = getCheckSumm16b(msg.data(), msg.size() - 2);

    QDataStream stream(&msg, QIODeviceBase::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    stream >> res.roll;
    stream >> res.pitch;
    stream >> res.yaw;
    stream >> res.depth;

    stream >> res.rollSpeed;
    stream >> res.pitchSpeed;
    stream >> res.yawSpeed;

    stream >> res.checksum;

    if (res.checksum != checksum_calc) {
        qDebug() << "Checksum NormalMessage is invalid";
        std::stringstream stream;
        stream << "[ISERVERDATA] Checksum is invalid. Calculated: [" <<
            std::ios::hex << checksum_calc << "] " <<
            "Received: [" <<
            std::ios::hex << res.checksum << "]";
        throw std::invalid_argument(stream.str());
    }

    pullFromStructure(res);
}

void IServerData::pullFromStructure(ResponseNormalMessage res) {
    UVMutex.lock();

    UVState.imu.roll = res.roll;
    UVState.imu.pitch = res.pitch;
    UVState.imu.yaw = res.yaw;
    UVState.imu.depth = res.depth;

    UVState.imu.rollSpeed = res.rollSpeed;
    UVState.imu.pitchSpeed = res.pitchSpeed;
    UVState.imu.yawSpeed = res.yawSpeed;

    UVMutex.unlock();
}

void IServerData::parseConfigMessage(QByteArray msg) {
    ResponseConfigMessage res;
    uint16_t checksum_calc = getCheckSumm16b(msg.data(), msg.size() - 2);

    QDataStream stream(&msg, QIODeviceBase::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    stream >> res.roll;
    stream >> res.pitch;
    stream >> res.yaw;
    stream >> res.depth;

    stream >> res.rollSpeed;
    stream >> res.pitchSpeed;
    stream >> res.yawSpeed;

    stream >> res.inputSignal;
    stream >> res.speedSignal;
    stream >> res.posSignal;

    stream >> res.joyUnitCasted;
    stream >> res.posError;
    stream >> res.joy_iValue;
    stream >> res.speedError;
    stream >> res.dynSummator;
    stream >> res.pidValue;
    stream >> res.posErrorAmp;
    stream >> res.speedFiltered;
    stream >> res.posFiltered;
    stream >> res.pid_iValue;
    stream >> res.pid_pValue;
    stream >> res.outputSignal;

    stream >> res.checksum;

    if (res.checksum != checksum_calc) {
        qDebug() << "Checksum ConfigMessage is invalid";
        std::stringstream stream;
        stream << "[ISERVERDATA] Checksum is invalid. Calculated: [" <<
            std::ios::hex << checksum_calc << "] " <<
            "Received: [" <<
            std::ios::hex << res.checksum << "]";
        throw std::invalid_argument(stream.str());
    }

    pullFromStructure(res);
}

void IServerData::pullFromStructure(ResponseConfigMessage res) {
    UVMutex.lock();

    UVState.imu.roll = res.roll;
    UVState.imu.pitch = res.pitch;
    UVState.imu.yaw = res.yaw;
    UVState.imu.depth = res.depth;

    UVState.imu.rollSpeed = res.rollSpeed;
    UVState.imu.pitchSpeed = res.pitchSpeed;
    UVState.imu.yawSpeed = res.yawSpeed;

    UVState.controlContour[UVState.currentControlContour].state.inputSignal = res.inputSignal;
    UVState.controlContour[UVState.currentControlContour].state.speedSignal = res.speedSignal;
    UVState.controlContour[UVState.currentControlContour].state.posSignal = res.posSignal;

    UVState.controlContour[UVState.currentControlContour].state.joyUnitCasted = res.joyUnitCasted;
    UVState.controlContour[UVState.currentControlContour].state.posError = res.posError;
    UVState.controlContour[UVState.currentControlContour].state.joy_iValue = res.joy_iValue;
    UVState.controlContour[UVState.currentControlContour].state.speedError = res.speedError;
    UVState.controlContour[UVState.currentControlContour].state.dynSummator = res.dynSummator;
    UVState.controlContour[UVState.currentControlContour].state.pidValue = res.pidValue;
    UVState.controlContour[UVState.currentControlContour].state.posErrorAmp = res.posErrorAmp;
    UVState.controlContour[UVState.currentControlContour].state.speedFiltered = res.speedFiltered;
    UVState.controlContour[UVState.currentControlContour].state.posFiltered = res.posFiltered;
    UVState.controlContour[UVState.currentControlContour].state.pid_iValue = res.pid_iValue;
    UVState.controlContour[UVState.currentControlContour].state.pid_pValue = res.pid_pValue;
    UVState.controlContour[UVState.currentControlContour].state.outputSignal = res.outputSignal;

    UVMutex.unlock();
}

void IServerData::parseDirectMessage(QByteArray msg) {
    ResponseDirectMessage res;

    uint16_t checksum_calc = getCheckSumm16b(msg.data(), msg.size() - 2);

    QDataStream stream(&msg, QIODeviceBase::ReadOnly);

    stream >> res.id;

    stream >> res.checksum;

    if (res.checksum != checksum_calc) {
        std::stringstream stream;
        stream << "[ISERVERDATA] Checksum is invalid. Calculated: [" <<
            std::ios::hex << checksum_calc << "] " <<
            "Received: [" <<
            std::ios::hex << res.checksum << "]";
        throw std::invalid_argument(stream.str());
    }

    pullFromStructure(res);
}

void IServerData::pullFromStructure(ResponseDirectMessage res) {
    // nothing
}

/* CRC16-CCITT algorithm */
uint16_t getCheckSumm16b(char* pcBlock, int len) {
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

void set_bit(uint8_t& byte, uint8_t bit, bool state) {
    uint8_t value = 1;
    if (state) {
        byte = byte | (value << bit);
    } else {
        byte = byte & ~(value << bit);
    }
}
