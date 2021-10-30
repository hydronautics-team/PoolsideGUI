#ifndef CONTROL_H
#define CONTROL_H

#include "Keyboard.h"
#include "Joystick.h"
#include "Mouse3d.h"

class Control : public QObject {
Q_OBJECT

public:
    Control();

    enum e_controllerType {
        JOYSTICK,
        KEYBOARD,
        MOUSE3D
    };

    Keyboard *keyboard;
    Mouse3d *mouse3D;
    Joystick *joystick;
    void enableController(e_controllerType controlType, bool mode);

};

#endif // CONTROL_H
