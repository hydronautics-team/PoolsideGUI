#include "picframe.h"

PicFrame::PicFrame(QWidget *parent) :
        QFrame(parent) {
    setupUi(this);
    setYaw(0);
}

void PicFrame::paintEvent(QPaintEvent *e) {
    QPainter painter;
    painter.begin(this);
    QFont font;
    painter.setRenderHint(QPainter::Antialiasing, true); // сглаживание
    painter.translate(width() / 2, height() / 2); // перенос системы координат
    int side = qMin(width(), height());
    painter.scale(side / 200, side / 200); // масштабирование СК
    painter.save();
    painter.rotate(yaw);
    painter.drawConvexPolygon(arrowCompass, 6);
    painter.restore();
    painter.save();
    painter.drawEllipse(-60, -60, 120, 120);
    painter.drawEllipse(-70, -70, 140, 140);
    for (int i = 0; i < 60; i++) {
        if ((i % 5) != 0)
            painter.drawLine(0, -55, 0, -60);
        else {
            painter.drawLine(0, -50, 0, -60);
            font.setPointSize(5);
            painter.setFont(font);
            painter.drawText(-20, -85, 40, 40, Qt::AlignCenter | Qt::AlignTop, QString::number(i * 6));
        }
        painter.rotate(6.0);
    }
    painter.setBrush(Qt::gray);
    painter.drawRect(-15, -5, 30, 10);
    font.setPointSize(10);
    painter.drawText(-20, -10, 40, 20, Qt::AlignCenter, QString::number(yaw));
    painter.restore();
}

void PicFrame::setYaw(double yawNew) {
    yaw = yawNew;
    update();
}
