#include "Control.h"

Control::Control() {

}

void Control::setDefoultEnabeling() {
    this->setEnabel(JOYSTICK, false);
    this->setEnabel(MOUSE3D, true);
    this->setEnabel(KEYBOARD, false);

};

void Control::setEnabel(e_controllerType controlType, bool enabel) {
    switch (controlType) {

        case JOYSTICK:
            if ((enabel == true) & (joystick == nullptr)) {
                joystick = new Joystick("Joystick", 10, 0);
            } else if (joystick != nullptr) {
                delete joystick;
                joystick = nullptr;
            }
            break;

        case MOUSE3D:
            if ((enabel == true) & (mouse3D == nullptr)) {
                mouse3D = new Mouse3d("3dMouse", 5);
            } else if (mouse3D != nullptr) {
                delete mouse3D;
                mouse3D = nullptr;
            }
            break;

        case KEYBOARD:
            if ((enabel == true) & (keyboard == nullptr)) {
                keyboard = new Keyboard("KeyBoard", 5);
            } else if (keyboard != nullptr) {
                delete keyboard;
                keyboard = nullptr;
            }
            break;
    }
}
