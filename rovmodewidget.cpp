#include "rovmodewidget.h"
#include <QDebug>

ROVModeWidget::ROVModeWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    qDebug () << " - ROVModeWidget constructor";

    settingsFile = QApplication::applicationDirPath() + "/settings.ini"; // path to settings file
    settings = new QSettings(settingsFile, QSettings::IniFormat);

    currentVehicle = settings->value("currentVehicle").toString();
    currentConfiguration = settings->value("currentConfiguration").toString();

    connect(this, SIGNAL(updateCompass(double)), compassFrame, SLOT(setYaw(double)));

    // add bars in group to easily access
    thrusterBarGroup.append(thrusterBar0);
    thrusterBarGroup.append(thrusterBar1);
    thrusterBarGroup.append(thrusterBar2);
    thrusterBarGroup.append(thrusterBar3);
    thrusterBarGroup.append(thrusterBar4);
    thrusterBarGroup.append(thrusterBar5);
    thrusterBarGroup.append(thrusterBar6);
    thrusterBarGroup.append(thrusterBar7);

    scene = new QGraphicsScene(vehiclePic);
    vehiclePic->setScene(scene);
    vehiclePic->setStyleSheet("background: transparent");
    vehiclePic->setRenderHint(QPainter::Antialiasing);

    initializeData();
    updateData();

    picROV = scene->addPixmap(QPixmap(":/images/Cousteau III.png"));
    picROV->setTransform(QTransform::fromScale(0.2, 0.2));
}

void ROVModeWidget::updateVehicle()
{
    currentVehicle = settings->value("currentVehicle").toString();
    thrustersCount = settings->value("vehicle/" +
                                     currentVehicle +
                                     "/thrusters/count").toInt();
    //update bars
    foreach (QProgressBar *bar, thrusterBarGroup) {
        bar->hide();
    }
    for (int i = 0; i < thrustersCount; i++){
        thrusterBarGroup[i]->show();
        thrusterBarGroup[i]->setFormat(settings->value(
                                           "vehicle/" +
                                           currentVehicle +
                                           "/thrusters/" +
                                           QString::number(i) +
                                           "/name").toString());
    }
    initializeData();
    updateData();
}

void ROVModeWidget::initializeData()
{
    foreach (QProgressBar *bar, thrusterBarGroup) {
        bar->setValue(0);
    }
    pitchBar->setValue(0);
    depthBar->setValue(0);
    depthLabel->setText("0");   // label under bar
    pitchLabel->setText("0");   // label under bar
    sensorsDepthLabel->setText("0");
    sensorsPitchLabel->setText("0");
    sensorsYawLabel->setText("0");
    sensorsRollLabel->setText("0");
    emit updateCompass(0);
}

void ROVModeWidget::updateData()
{
    IBasicData interface(&UVState, &UVMutex);
    interface.getData();
    depthBar->setValue(static_cast<int>(interface.internal_state.sensors_depth));   // bar
    pitchBar->setValue(static_cast<int>(interface.internal_state.sensors_pitch));   // bar
    depthLabel->setText(QString::number(interface.internal_state.sensors_depth));   // label under bar
    pitchLabel->setText(QString::number(interface.internal_state.sensors_pitch));   // label under bar
    sensorsDepthLabel->setText(QString::number(interface.internal_state.sensors_depth));
    sensorsPitchLabel->setText(QString::number(interface.internal_state.sensors_pitch));
    sensorsYawLabel->setText(QString::number(interface.internal_state.sensors_yaw));
    sensorsRollLabel->setText(QString::number(interface.internal_state.sensors_roll));
    emit updateCompass(interface.internal_state.sensors_yaw);
}
