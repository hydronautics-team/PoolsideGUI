#ifndef UV_THRUSTERS_H
#define UV_THRUSTERS_H

#include <QString>


class UV_Thrusters
{
public:
    UV_Thrusters();

    QString name;

    int id;
    int slot;

    bool reverse;

    double kForward;
    double kBackward;

    int8_t sForward;
    int8_t sBackward;

    int8_t velocity;
};

#endif // UV_THRUSTERS_H
