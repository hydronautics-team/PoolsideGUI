#include "joystick.h"

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
    {sf::Joystick::R, 1, SET_YAW},
    {sf::Joystick::Y, 1, SET_MARCH},
    {sf::Joystick::X, 1, SET_LAG},
    {sf::Joystick::U, 1, SET_DEPTH}
};

const Joystick::control_buttons Joystick::buttons_table[] = {
    {0, 127, CLENCH_GRAB, 1},
    {1, 127, UNCLENCH_GRAB, 0},
    {2, 127, ROTATE_GRAB_LEFT, 3},
    {3, 127, ROTATE_GRAB_RIGHT, 2},
    {4, 127, ROTATE_TILT_UP, 5},
    {5, 127, ROTATE_TILT_DOWN, 4}
};

Joystick::Joystick(QString name, int update_time, unsigned int joy_id) :
    ControlBase(name, update_time)
{
    id = joy_id;

    update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateDevice()));
    update_timer->start(update_time);
}

void Joystick::updateDevice()
{
    sf::Joystick::update();

    for(unsigned int i=0; i<sizeof(axis_table)/sizeof(axis_table[0]); i++) {
        sendAction(axis_table[i].action, (sf::Joystick::getAxisPosition(id, axis_table[i].axis) * axis_table[i].multiplier));
    }

    QVector<int> ignore_press;
    ignore_press.clear();

    for(unsigned int i=0; i<sizeof(buttons_table)/sizeof(buttons_table[0]); i++) {
        if(sf::Joystick::isButtonPressed(id, buttons_table[i].button_id)) {
            sendAction(buttons_table[i].action, buttons_table[i].setterValue);
            ignore_press.append(buttons_table[i].antagonist);
        }
        else {
            bool ignore = false;
            for(int j=0; j<ignore_press.size(); j++) {
                if(ignore_press[j] == i) {
                    ignore = true;
                }
            }

            if(ignore) {
                continue;
            }
            sendAction(buttons_table[i].action, 0);
        }
    }
}
