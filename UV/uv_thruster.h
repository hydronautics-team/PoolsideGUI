#ifndef UV_THRUSTERS_H
#define UV_THRUSTERS_H

#include <QString>


class UV_Thruster {
public:
    UV_Thruster();

    QString name;

    bool power;

    int id;
    int slot;

    bool reverse;

    double kForward;
    double kBackward;

    int8_t sForward;
    int8_t sBackward;

    double velocity;
    double current;
};

#endif // UV_THRUSTERS_H
