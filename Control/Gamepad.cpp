#include "Gamepad.h"

const Gamepad::control_axis Gamepad::axis_table[] = {
        {sf::Joystick::V,       SET_MARCH,  320},
        {sf::Joystick::X,       SET_LAG,    320},
        {sf::Joystick::U,       SET_YAW,    320},
        {sf::Joystick::PovY,    TILT,       1.27},
        {sf::Joystick::R,       SET_DEPTH,  160},
        {sf::Joystick::Z,       SET_DEPTH,  160},
};

const Gamepad::control_buttons Gamepad::buttons_table[] = {
        {0, 1, GRAB,        127},
        {2, 3, GRAB_ROTATE, 127},
};

Gamepad::Gamepad(int updateTimeMs): ControlBase("Gamepad") {
    update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateDevice()));
    update_timer->start(updateTimeMs);
}

void Gamepad::updateDevice() {
    sf::Joystick::update();

    for (unsigned int i = 0; i < sizeof(axis_table) / sizeof(axis_table[0]) - 2; i++) {
        sendAction(axis_table[i].action,
            sf::Joystick::getAxisPosition(id, axis_table[i].axis) * axis_table[i].multiplier);
    }

    sendAction(SET_DEPTH,
        (sf::Joystick::getAxisPosition(id, axis_table[4].axis) * axis_table[4].multiplier) -
        (sf::Joystick::getAxisPosition(id, axis_table[5].axis) * axis_table[5].multiplier));

    for (unsigned int i = 0; i < sizeof(buttons_table) / sizeof(buttons_table[0]); i++) {
        if (sf::Joystick::isButtonPressed(id, buttons_table[i].button_id) and
            sf::Joystick::isButtonPressed(id, buttons_table[i].button_idReverse)) {
            sendAction(buttons_table[i].action, static_cast<int8_t>(0));
            continue;
        } else if (sf::Joystick::isButtonPressed(id, buttons_table[i].button_id)) {
            sendAction(buttons_table[i].action, buttons_table[i].setterValue);
            continue;
        } else if (sf::Joystick::isButtonPressed(id, buttons_table[i].button_idReverse)) {
            sendAction(buttons_table[i].action, static_cast<int8_t>(-buttons_table[i].setterValue));
            continue;
        } else {
            sendAction(buttons_table[i].action, static_cast<int8_t>(0));
            continue;
        }
    }
}
