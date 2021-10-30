#include "Control.h"

Control::Control() {

}

void Control::enableController(e_controllerType controlType, bool mode) {
    switch (controlType) {
        case JOYSTICK:
            if (mode == true) {
                joystick = new Joystick("Joystick", 10, 0);
            } else {
                delete joystick;
            }
            break;

        case MOUSE3D:
            if (mode == true) {
                mouse3D = new Mouse3d("3dMouse", 5);
            } else {
                delete mouse3D;
            }
            break;

        case KEYBOARD:
            if (mode == true) {
                keyboard = new Keyboard("KeyBoard", 5);
            } else {
                delete keyboard;
            }
            break;
    }
}
