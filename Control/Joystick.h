#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "ControlBase.h"
#include "SFML/Window.hpp"

class Joystick: public ControlBase {
    Q_OBJECT

public:
    Joystick(int updateTimeMs);

public slots:

    void updateDevice();

private:
    int id = 0;
    QTimer* update_timer;

    struct control_axis {
        sf::Joystick::Axis axis;
        e_actionTypes action;
        float multiplier;
    };

    struct control_buttons {
        unsigned int button_id;
        unsigned int button_idReverse;
        e_actionTypes action;
        int8_t setterValue;
    };

    const static control_axis axis_table[];
    const static control_buttons buttons_table[];
};

#endif // JOYSTICK_H
