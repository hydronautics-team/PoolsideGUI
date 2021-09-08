#ifndef CONTROLBASE_H
#define CONTROLBASE_H

#include <QTimer>
#include "UV/icontroldata.h"
#include "qmath.h"

class ControlBase :
        public QObject
{
    Q_OBJECT

public:
    ControlBase(QString name, int update_time);

protected:
    QString device_name;

    enum e_actionTypes {
        SET_MARCH = 0,
        SET_LAG,
        SET_DEPTH,
        SET_ROLL,
        SET_PITCH,
        SET_YAW,
        SET_TILT,
        CLENCH_GRAB,
        UNCLENCH_GRAB,
        ROTATE_GRAB_RIGHT,
        ROTATE_GRAB_LEFT,
        ROTATE_TILT_UP,
        ROTATE_TILT_DOWN
        };

    void sendAction(e_actionTypes type, double value);

    void setMarch(double value);
    void setLag(double value);
    void setDepth(double value);
    void setRoll(double value);
    void setPitch(double value);
    void setYaw(double value);
    void setTilt(double value);
    void clenchGrab(double value);
    void unclenchGrab(double value);
    void rotateGrabRight(double value);
    void rotateGrabLeft(double value);
    void rotateTiltUp(double value);
    void rotateTiltDown(double value);
    double Sensitivity(double value, double deadZone, double maxValue);
    double Sensitivity(double value, double deadZone,double pointX,double pointY, double maxValue);
private:
    IControlData interface;
};

#endif // CONTROLBASE_H
