#ifndef PICFRAME_H
#define PICFRAME_H

#include "ui_picframe.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <cmath>

class PicFrame : public QFrame, private Ui::PicFrame
{
    Q_OBJECT

public:
    explicit PicFrame(QWidget *parent = nullptr);

public slots:
    void setYaw(double yawNew);

protected:
    void paintEvent(QPaintEvent *e);

private:
    double yaw;
    QPoint arrowCompass[6] = {
        QPoint(0, 50),
        QPoint(0, -50),
        QPoint(3, -40),
        QPoint(0, -50),
        QPoint(-3, -40),
        QPoint(0, -50),
    };
    QPoint arrowDesirable[3] = {
        QPoint(0, -70),
        QPoint(5, -85),
        QPoint(-5, -85),
        //QPoint(0, -50)
    };
};

#endif // PICFRAME_H
