#ifndef MOUSE_3D_H
#define MOUSE_3D_H

#include <QMainWindow>
#include <QTimer>
#include <QtDebug>
#include <QObject>
//#include <iostream>

#include "controlbase.h"
#include "hidapi.h"

class Mouse3d  : public ControlBase
{
    Q_OBJECT

public:
    Mouse3d(QString name, int update_time);
    hid_device *handle;
    unsigned char buf[7];

    struct mouseData {
        short int coords[6] = {0, 0, 0, 0, 0, 0};
        bool b1 = 0;
        bool b2 = 0;
    };
    mouseData mouseDta;

    void connect3dMouse();
    void parceCoordinate(unsigned char*, short int *);
    void parceAll(unsigned char*, mouseData*);

private:
    QTimer *update_timer;

    struct control_axis {
        int axis;
        double multiplier;
        e_actionTypes action;
    };

    const static control_axis axis_table[];

public slots:
    void updateDevice();

};


#endif // MOUSE_3D_H
