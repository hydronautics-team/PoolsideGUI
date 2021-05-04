#ifndef MOUSE_3D_H
#define MOUSE_3D_H

#include <QMainWindow>
#include <QTimer>
#include <QtDebug>
#include <QObject>
#include <iostream>

#include "hidapi.h"

class Mouse3d : public QObject
{
    Q_OBJECT

public:
    Mouse3d();
    hid_device *handle;
    unsigned char buf[7];

    struct mouseData {
        short int coords[6] = {0, 0, 0, 0, 0, 0};
        bool b1 = 0;
        bool b2 = 0;
    };
    mouseData* mouse;

    void connect3dMouse();
    void parceCoordinate(unsigned char*, short int &);
    void parceAll(unsigned char*, mouseData*);

private:
    QTimer *update_timer;

public slots:
    void updateDevice();

};


#endif // MOUSE_3D_H
