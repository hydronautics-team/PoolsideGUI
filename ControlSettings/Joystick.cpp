#include "Joystick.h"

/*
схват зажать 0
схват разжать 1
ротация лево 2
ротация право 3
axial r - курс
axial y - марш
axial x - лаг

axial u - глубина
*/

const Joystick::control_axis Joystick::axis_table[] = {
        {sf::Joystick::R,    -2,  SET_YAW},
        {sf::Joystick::Y,    -320, SET_MARCH},
        {sf::Joystick::X,    320,  SET_LAG},
        {sf::Joystick::Z,    -20,  SET_DEPTH},
        {sf::Joystick::PovX, 200,  SET_ROLL},
        {sf::Joystick::PovY, 200,  SET_PITCH}
};

Joystick::Joystick(QString name, int update_time, unsigned int joy_id) :
        ControlBase(name, update_time) {
    id = joy_id;

    update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateDevice()));
    update_timer->start(update_time);
}

void Joystick::updateDevice() {
    sf::Joystick::update();

    for (unsigned int i = 0; i < sizeof(axis_table) / sizeof(axis_table[0]); i++) {
        if (axis_table[i].axis == sf::Joystick::Y) { marchTrim = sf::Joystick::getAxisPosition(id, axis_table[i].axis) *
                                                                 axis_table[i].multiplier;
        }
        if (axis_table[i].axis == sf::Joystick::R) { yawTrim = sf::Joystick::getAxisPosition(id, axis_table[i].axis) *
                                                               axis_table[i].multiplier;
        }
        sendAction(axis_table[i].action,
                   (sf::Joystick::getAxisPosition(id, axis_table[i].axis) * axis_table[i].multiplier));
    }
}
