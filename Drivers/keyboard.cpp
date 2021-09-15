#include "keyboard.h"
#define SETTER_VALUE 32000

Keyboard::Keyboard(QString name, int update_time) :
        ControlBase(name, update_time)
{
    update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateKeyboard()));
    update_timer -> start(update_time);
}

const Keyboard::control_buttons Keyboard::buttons_table[] = {
        {sf::Keyboard::D,1, SETTER_VALUE, SET_LAG},
        {sf::Keyboard::A,0, -SETTER_VALUE, SET_LAG},
        {sf::Keyboard::W,3, SETTER_VALUE, SET_MARCH},
        {sf::Keyboard::S,2, -SETTER_VALUE, SET_MARCH},
        {sf::Keyboard::E,5, SETTER_VALUE, SET_YAW},
        {sf::Keyboard::Q,4, -SETTER_VALUE, SET_YAW},
        {sf::Keyboard::LShift,7, SETTER_VALUE, SET_DEPTH},
        {sf::Keyboard::LControl,6, -SETTER_VALUE, SET_DEPTH},

        {sf::Keyboard::R, 9, 30, ROTATE_TILT_UP},
        {sf::Keyboard::F, 8, 30, ROTATE_TILT_DOWN},
        {sf::Keyboard::Space, 11, 127, CLENCH_GRAB},
        {sf::Keyboard::C, 10, 127, UNCLENCH_GRAB},
        {sf::Keyboard::X, 13, 125, ROTATE_GRAB_LEFT},
        {sf::Keyboard::V, 12, 125, ROTATE_GRAB_RIGHT},
};

void Keyboard::updateKeyboard()
{
    QVector<unsigned int> ignore_press;
    ignore_press.clear();

    for(unsigned int i=0; i<sizeof(buttons_table)/sizeof(buttons_table[0]); i++) {
        if(sf::Keyboard::isKeyPressed(buttons_table[i].Key)) {
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