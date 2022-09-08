#ifndef CONTROLBASE_H
#define CONTROLBASE_H

#include <QTimer>
#include "UV/icontroldata.h"
#include "qmath.h"

class ControlBase : public QObject {
Q_OBJECT

public:
    ControlBase(QString name, int update_time);

signals:
    void controlChanged();

protected:
    QString device_name;

    enum e_actionTypes {
        SET_MARCH = 0,
        SET_LAG,
        SET_DEPTH,
        SET_ROLL,
        SET_PITCH,
        SET_YAW,
    };

    void sendAction(e_actionTypes type, float value);

    void setMarch(float value);
    void setLag(float value);
    void setDepth(float value);
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);

    double Sensitivity(double value, double deadZone, double maxValue);
    double Sensitivity(double value, double deadZone, double pointX, double pointY, double maxValue);

private:
    IControlData interface;
};

#endif // CONTROLBASE_H
