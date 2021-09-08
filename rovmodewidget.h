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
#include "ui_rovmodewidget.h"
#include "PicFrame/picframe.h"

#include "UV/iuserinterfacedata.h"

class ROVModeWidget : public QWidget, private Ui::ROVModeWidget
{
    Q_OBJECT

signals:
    void updateCompass(double yaw);

public:
    explicit ROVModeWidget(QWidget *parent = nullptr);
    float depthLin = 9.9546;
    float depthOffset = 0;
    QPushButton* getPushButtonReconnectROV();

public slots:
    void updateVehicle();
    void updateData();
    void checkboxChecked(int i);
    void resetImu();
    void clearResetImu();

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

    // Interface for accessing UVState object
    IUserInterfaceData uv_interface;

    void initializeData();

};

#endif // ROVMODEWIDGET_H
