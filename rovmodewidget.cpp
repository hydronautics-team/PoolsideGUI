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

    initializeWindow();
}

void ROVModeWidget::updateVehicle()
{
    currentVehicle = settings->value("currentVehicle").toString();
    thrustersCount = settings->value("vehicle/" +
                                     currentVehicle +
                                     "/thrusters/count").toInt();
    //update buttons
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
    //updateThrusterSettings();
}

void ROVModeWidget::initializeWindow()
{
    // add bars in group to easily access
    thrusterBarGroup.append(thrusterBar0);
    thrusterBarGroup.append(thrusterBar1);
    thrusterBarGroup.append(thrusterBar2);
    thrusterBarGroup.append(thrusterBar3);
    thrusterBarGroup.append(thrusterBar4);
    thrusterBarGroup.append(thrusterBar5);
    thrusterBarGroup.append(thrusterBar6);
    thrusterBarGroup.append(thrusterBar7);

    foreach (QProgressBar *bar, thrusterBarGroup) {
        bar->setValue(0);
    }
    pitchBar->setValue(0);
    depthBar->setValue(0);
}

void ROVModeWidget::updateWindow()
{

}
