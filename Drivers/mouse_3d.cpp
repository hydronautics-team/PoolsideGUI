#include "mouse_3d.h"

const Mouse3d::control_axis Mouse3d::axis_table[] = {
    {91, SET_LAG},
    {-91, SET_MARCH},
    {91, SET_DEPTH},
    {91, SET_PITCH},
    {91, SET_ROLL},
    {91, SET_YAW},
};

const Mouse3d::control_buttons Mouse3d::buttons_table[] = {
    {sf::Keyboard::Q, 1, 30, ROTATE_TILT_UP},
    {sf::Keyboard::E, 0, 30, ROTATE_TILT_DOWN},
    {sf::Keyboard::Space, 3, 127, CLENCH_GRAB},
    {sf::Keyboard::S, 2, 127, UNCLENCH_GRAB},
    {sf::Keyboard::A, 5, 125, ROTATE_GRAB_LEFT},
    {sf::Keyboard::D, 4, 125, ROTATE_GRAB_RIGHT},

};

Mouse3d::Mouse3d(QString name, int update_time) :
    ControlBase(name, update_time)
{
    handle = hid_open(0x256f, 0xc635, NULL);
    if (handle) {
        qDebug () <<"3dmouse connected" << endl;

        hid_set_nonblocking(handle, 1);

        update_timer = new QTimer(this);
        connect(update_timer, SIGNAL(timeout()), this, SLOT(updateDevice()));
        update_timer -> start(update_time);
    }
    else {
        update_timer = new QTimer(this);
        connect(update_timer, SIGNAL(timeout()), this, SLOT(updateKeyboardOnly()));
        update_timer -> start(update_time);
    }
}

void Mouse3d::updateDevice() {
    if (handle) {
        hid_read(handle, buf, 7);
        Mouse3d::parseMouse(buf, &mouseDta);

        for(unsigned int i=0; i<sizeof(axis_table)/sizeof(axis_table[0]); i++) {
            sendAction(axis_table[i].action, (mouseDta.coords[i] * axis_table[i].multiplier));
        }
    }

    if(((mouseDta.b2 == 0)||!(sf::Keyboard::isKeyPressed(buttons_table[1].Key)))
                &(((mouseDta.b1 == 0)||!(sf::Keyboard::isKeyPressed(buttons_table[0].Key))))){
        sendAction(buttons_table[0].action, 0);
    }
    if(((mouseDta.b1 == 1)||(sf::Keyboard::isKeyPressed(buttons_table[0].Key)))
            &(((mouseDta.b2 == 0)||!(sf::Keyboard::isKeyPressed(buttons_table[1].Key))))){
        sendAction(buttons_table[0].action, buttons_table[0].setterValue);
    }
    else if (((mouseDta.b2 == 1)||(sf::Keyboard::isKeyPressed(buttons_table[1].Key)))
             &(((mouseDta.b1 == 0)||!(sf::Keyboard::isKeyPressed(buttons_table[0].Key))))){
        sendAction(buttons_table[1].action, buttons_table[1].setterValue);
    }
    else {
        sendAction(buttons_table[1].action, 0);
    }

    QVector<unsigned int> ignore_press;
    ignore_press.clear();

    for(unsigned int i=2; i<sizeof(buttons_table)/sizeof(buttons_table[0]); i++) {
        if(sf::Keyboard::isKeyPressed(buttons_table[i].Key)) {
            sendAction(buttons_table[i].action, buttons_table[i].setterValue);
            qDebug () << buttons_table[i].Key;
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

void Mouse3d::updateKeyboardOnly()
{
    QVector<unsigned int> ignore_press;
    ignore_press.clear();

    for(unsigned int i=0; i<sizeof(buttons_table)/sizeof(buttons_table[0]); i++) {
        if(sf::Keyboard::isKeyPressed(buttons_table[i].Key)) {
            sendAction(buttons_table[i].action, buttons_table[i].setterValue);
            qDebug () << buttons_table[i].Key;
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

void Mouse3d::parseCoordinate(unsigned char* buf, short int *coordPosition) {
    if (static_cast<short int>(buf[1]) == 0) {
        *coordPosition = static_cast<short int>(buf[0]);
    }
    else if (static_cast<short int>(buf[1]) == 1) {
        *coordPosition = 255 + static_cast<short int>(buf[0]);
    }
    else if (static_cast<short int>(buf[1]) == 255) {
        *coordPosition = - 255 + static_cast<short int>(buf[0]);
    }
    else if (static_cast<short int>(buf[1]) == 254) {
        *coordPosition = - 511 + static_cast<short int>(buf[0]);
    }
}

void Mouse3d::parseMouse(unsigned char* buf, mouseData* mouse)
{
    if (static_cast<short int>(buf[0]) == 1) {
        for (int i = 0; i < 3; i++) {
            Mouse3d::parseCoordinate(&buf[2 * i + 1], &mouse->coords[i]);
        }
    }
    else if (static_cast<short int>(buf[0]) == 2) {
        for (int i = 0; i < 3; i++) {
            Mouse3d::parseCoordinate(&buf[2 * i + 1], &mouse->coords[i + 3]);
        }
    }
    else if (static_cast<short int>(buf[0]) == 3) {
        if (static_cast<short int>(buf[1]) == 0) {
            mouse->b1 = 0;
            mouse->b2 = 0;
        }
        else if (static_cast<short int>(buf[1]) == 1) {
            mouse->b1 = 1;
            mouse->b2 = 0;
        }
        else if (static_cast<short int>(buf[1]) == 2) {
            mouse->b1 = 0;
            mouse->b2 = 1;
        }
        else if (static_cast<short int>(buf[1]) == 3) {
            mouse->b1 = 1;
            mouse->b2 = 1;
        }
    }
}
