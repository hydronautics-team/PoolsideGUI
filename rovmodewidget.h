#ifndef ROVMODEWIDGET_H
#define ROVMODEWIDGET_H

#include <QSettings>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include "UV/uv_state.h"
#include "UV/ibasicdata.h"
#include "global.h"
#include "ui_rovmodewidget.h"
#include "PicFrame/picframe.h"

class ROVModeWidget : public QWidget, private Ui::ROVModeWidget
{
    Q_OBJECT

signals:
    void updateCompass(double yaw);

public:
    explicit ROVModeWidget(QWidget *parent = nullptr);

public slots:
    void updateVehicle();
    void updateData();

private:
    QString settingsFile;
    QSettings *settings;
    QString currentVehicle;
    QString currentConfiguration;
    int thrustersCount;
    QList<QProgressBar *> thrusterBarGroup;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *picROV;
    QGraphicsTextItem *txtCurrentYaw;


    void initializeData();

};

#endif // ROVMODEWIDGET_H
