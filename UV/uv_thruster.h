#ifndef UV_THRUSTERS_H
#define UV_THRUSTERS_H

#include <QString>


class UV_Thruster {
public:
    UV_Thruster();

    QString name;

    bool power = false;

    int id;
    int adress;

    double velocity;

    bool reverse;
    int8_t kForward;
    int8_t kBackward;

    int8_t sForward;
    int8_t sBackward;
};

#endif // UV_THRUSTERS_H
