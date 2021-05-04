#include "mouse_3d.h"

Mouse3d::Mouse3d()
{
    update_timer = new QTimer(this);
    handle = hid_open(0x256f, 0xc635, NULL);
    hid_set_nonblocking(handle, 0);

//    int *a = 0;
//    short b = 0;
//    short c = 0;

    update_timer -> start(5);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateDevice()));
}


void Mouse3d::updateDevice() {
    if (handle) {
        hid_read(handle, buf, 7);

//        DATA_IN = QByteArray(reinterpret_cast<char*>(buf), 7); //DATA_IN is the received data
/*        std::cout << "3D CONNEXIO ";
        for(int i = 0; i < 7; i++) {
//            std::cout << static_cast<short int>(buf[i]) << ' ';
//            qDebug() << static_cast<short int>(buf[i]) << ' ';


        }
//        MainWindow::parceCoordinate(&buf[1], a);
//        std::cout << a << ' ';
//        a = &buf[1]; */

        Mouse3d::parceAll(buf, mouse);
        Mouse3d::parceAll(buf, mouse);

        for (int i = 0; i < 6; i++) {
            std::cout << mouse->coords[i] << ' ';
        }
        std::cout << std::endl;
    }
}

void Mouse3d::parceCoordinate(unsigned char* buf, short int &coordPosition) {
    if (static_cast<short int>(buf[1]) == 0) {
        coordPosition = static_cast<int>(buf[0]);
    }
    else if (static_cast<short int>(buf[1]) == 1) {
        coordPosition = 255 + static_cast<short int>(buf[0]);
    }
    else if (static_cast<short int>(buf[1]) == 255) {
        coordPosition = - 255 + static_cast<int>(buf[0]);
    }
    else if (static_cast<short int>(buf[1]) == 254) {
        coordPosition = - 511 + static_cast<int>(buf[0]);
    }
}

void Mouse3d::parceAll(unsigned char* buf, mouseData* mouse)
{
    if (static_cast<short int>(buf[0]) == 1) {
        for (int i = 0; i < 3; i++) {
            Mouse3d::parceCoordinate(&buf[2 * i + 1], mouse->coords[i]);
        }
    }
    else if (static_cast<short int>(buf[0]) == 2) {
        for (int i = 0; i < 3; i++) {
            Mouse3d::parceCoordinate(&buf[2 * i + 1], mouse->coords[i + 3]);
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
