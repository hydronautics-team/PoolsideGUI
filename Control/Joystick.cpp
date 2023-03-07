#include "Joystick.h"

const Joystick::control_axis Joystick::axis_table[] = {
        {sf::Joystick::R,       SET_YAW,    320},
        {sf::Joystick::Y,       SET_MARCH,  320},
        {sf::Joystick::X,       SET_LAG,    320},
        {sf::Joystick::Z,       SET_DEPTH,  320},
        {sf::Joystick::PovY,    TILT,       2},
};

const Joystick::control_buttons Joystick::buttons_table[] = {
        {0, 1, GRAB,        127},
        {2, 3, GRAB_ROTATE, 127},
};

Joystick::Joystick(int updateTimeMs): ControlBase("Joystick") {
    update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateDevice()));
    update_timer->start(updateTimeMs);
}

void Joystick::updateDevice() {
    sf::Joystick::update();
    // qDebug() << "updateDevice";

    for (unsigned int i = 0; i < sizeof(axis_table) / sizeof(axis_table[0]); i++) {
        sendAction(axis_table[i].action,
            sf::Joystick::getAxisPosition(id, axis_table[i].axis) * axis_table[i].multiplier);
    }

    for (unsigned int i = 0; i < sizeof(buttons_table) / sizeof(buttons_table[0]); i++) {
        if (sf::Joystick::isButtonPressed(id, buttons_table[i].button_id) and
            sf::Joystick::isButtonPressed(id, buttons_table[i].button_idReverse)) {
            sendAction(buttons_table[i].action, float(0));
            continue;
        } else if (sf::Joystick::isButtonPressed(id, buttons_table[i].button_id)) {
            sendAction(buttons_table[i].action, buttons_table[i].setterValue);
            continue;
        } else if (sf::Joystick::isButtonPressed(id, buttons_table[i].button_idReverse)) {
            sendAction(buttons_table[i].action, -buttons_table[i].setterValue);
            continue;
        } else {
            sendAction(buttons_table[i].action, float(0));
            continue;
        }
    }
}
