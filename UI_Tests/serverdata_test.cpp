#include "serverdata_test.h"

#include <QTest>

Serverdata_Test::Serverdata_Test(QObject *parent)
{
    //ideal_message.append("\xAA\x00\x07\x00\x01\x00\x00\xC0\xC1\x00\x00\xC0\xC1\x7F\x7F&\x0B");

    ideal_message.append('\xAA');
    ideal_message.append('\x00');
    ideal_message.append('\x07');
    ideal_message.append('\x00');
    ideal_message.append('\x01');
    ideal_message.append('\x00');
    ideal_message.append('\x00');
    ideal_message.append('\x80');
    ideal_message.append('?');
    ideal_message.append('\x00');
    ideal_message.append('\x00');
    ideal_message.append('\x80');
    ideal_message.append('?');
    ideal_message.append('\x7F');
    ideal_message.append('\x7F');
    ideal_message.append('N');
    ideal_message.append('r');
}

void Serverdata_Test::directRequest()
{
// TODO do something with thruster selected

//    UV_State state;

//    state.ThrusterSelected = 0;
//    state.thrusters[0].kForward = -24;
//    state.thrusters[0].kBackward = -24;
//    state.thrusters[0].sForward = 127;
//    state.thrusters[0].sBackward = 127;
//    state.thrusters[0].velocity = 0;
//    state.thrusters[0].reverse = true;
//    state.thrusters[0].id = 7;

//    QMutex mutex;
//    IServerData sub(&state, &mutex);
//    QCOMPARE(sub.getMessage(MESSAGE_DIRECT), ideal_message);
//    QCOMPARE(a.max(-1,  1), 1);
//    QCOMPARE(a.max(4,   8), 8);
//    QCOMPARE(a.max(0,   0), 0);
//    QCOMPARE(a.max(1,   1), 1);
//    QCOMPARE(a.max(-10,-5), -5);
}
