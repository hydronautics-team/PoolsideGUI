#include "Keyboard.h"

#define SETTER_VALUE 45
#define SETTER_VALUE_DEPTH -100

Keyboard::Keyboard(QString name, int update_time) :
        ControlBase(name, update_time) {
    update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateKeyboard()));
    update_timer->start(update_time);
}

const Keyboard::control_buttons Keyboard::buttons_table[] = {
        {sf::Keyboard::D,        1, SETTER_VALUE * 300,   SET_LAG},
        {sf::Keyboard::A,        0,  -SETTER_VALUE * 300, SET_LAG},
        {sf::Keyboard::W,        3, SETTER_VALUE * 300,   SET_MARCH},
        {sf::Keyboard::Q,        2,  0, SET_MARCH},
        {sf::Keyboard::P,        2,  0, SET_LAG},
        {sf::Keyboard::S,        2,  -SETTER_VALUE * 300, SET_MARCH},
        {sf::Keyboard::Y,        5, 0,   SET_YAW},
        {sf::Keyboard::T,        5, -SETTER_VALUE,   SET_YAW},
        {sf::Keyboard::R,        5, -SETTER_VALUE * 2,   SET_YAW},
        {sf::Keyboard::E,        5, -SETTER_VALUE * 4,   SET_YAW},
        {sf::Keyboard::G,        5, -SETTER_VALUE * 10,   SET_YAW},
        {sf::Keyboard::U,        5, SETTER_VALUE,   SET_YAW},
        {sf::Keyboard::I,        5, SETTER_VALUE * 2,   SET_YAW},
        {sf::Keyboard::O,        4, SETTER_VALUE * 4, SET_YAW},
        {sf::Keyboard::J,        4, SETTER_VALUE * 10, SET_YAW},
        {sf::Keyboard::X, 7, 0,   SET_DEPTH},
        {sf::Keyboard::C, 7, SETTER_VALUE_DEPTH,   SET_DEPTH},
        {sf::Keyboard::V, 6, SETTER_VALUE_DEPTH * 2, SET_DEPTH},
        {sf::Keyboard::B, 6, SETTER_VALUE_DEPTH * 3, SET_DEPTH},
        {sf::Keyboard::N, 6, SETTER_VALUE_DEPTH * 5, SET_DEPTH},
        {sf::Keyboard::M, 6, SETTER_VALUE_DEPTH * 10, SET_DEPTH},
        {sf::Keyboard::K, 6, SETTER_VALUE_DEPTH * 15, SET_DEPTH},
        {sf::Keyboard::L, 6, - SETTER_VALUE_DEPTH * 10, SET_DEPTH},
        };

void Keyboard::updateKeyboard() {
    QVector<unsigned int> ignore_press;
    ignore_press.clear();

    for (unsigned int i = 0; i < sizeof(buttons_table) / sizeof(buttons_table[0]); i++) {
        if (sf::Keyboard::isKeyPressed(buttons_table[i].Key)) {
            sendAction(buttons_table[i].action, buttons_table[i].setterValue);
            ignore_press.append(buttons_table[i].antagonist);
//        } else {
//            bool ignore = false;
//            for (int j = 0; j < ignore_press.size(); j++) {
//                if (ignore_press[j] == i) {
//                    ignore = true;
//                }
//            }
//            if (ignore) {
//                continue;
//            }
//            sendAction(buttons_table[i].action, 0);
        }
    }
}