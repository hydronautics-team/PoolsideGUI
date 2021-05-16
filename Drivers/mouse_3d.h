#ifndef MOUSE_3D_H
#define MOUSE_3D_H

#include <QMainWindow>
#include <QTimer>
#include <QtDebug>
#include <QObject>

#include "controlbase.h"
#include "SFML/Window.hpp"
#include "hidapi.h"

class Mouse3d  : public ControlBase
{
    Q_OBJECT

public:
    Mouse3d(QString name, int update_time);
    hid_device *handle;
    unsigned char buf[7]; // представляет из себя 7 байт: 1-й байт определяет что будет приходит (поступательное движение, вращательное или кнопки)

    struct mouseData {
        short int coords[6] = {0, 0, 0, 0, 0, 0}; // x, y, z, x rotation, y rotation, z rotation
        bool b1 = 0;
        bool b2 = 0;
    };
    mouseData mouseDta;

    bool keyboardData[4] = {0, 0, 0, 0};

    void connect3dMouse();
    void parseCoordinate(unsigned char*, short int *); // парсит 2 байта из buf
    void parseMouse(unsigned char*, mouseData*); // парсит все координаты и кнопки

private:
    QTimer *update_timer;

    struct control_axis {
        double multiplier;
        e_actionTypes action;
    };

    struct control_buttons {
        sf::Keyboard::Key Key;
        int antagonist;
        double setterValue;
        e_actionTypes action;
    };

    const static control_axis axis_table[];
    const static control_buttons buttons_table[];

public slots:
    void updateDevice();
    void updateKeyboardOnly();

};


#endif // MOUSE_3D_H
