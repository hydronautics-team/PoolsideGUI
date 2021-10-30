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

    Keyboard *keyboard = nullptr;
    Mouse3d *mouse3D = nullptr;
    Joystick *joystick = nullptr;
    void setDefoultEnabeling();
    void setEnabel(e_controllerType controlType, bool enabel);

};

#endif // CONTROL_H
