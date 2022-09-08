#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "ControlBase.h"
#include "SFML/Window.hpp"
#include <QVector>
#include <QDebug>

class Joystick : public ControlBase {
Q_OBJECT

public:
    Joystick(QString name, int update_time, unsigned int joy_id);

    int getID();

    float marchTrim, yawTrim;
    float marchYawTrim = -0.2;
    bool ignoreAxis = false;
    int ignoreAxisID = 6;

public slots:

    void updateDevice();

private:
    int id;
    QTimer *update_timer;

    /* Axis processing table element structure */
    struct control_axis {
        sf::Joystick::Axis axis;
        double multiplier;
        e_actionTypes action;
    };

    const static control_axis axis_table[];
};

#endif // JOYSTICK_H
