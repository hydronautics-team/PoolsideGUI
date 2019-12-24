#include "thrustersettings.h"
#include <QDebug>
#include <QFileInfo>

ThrusterSettings::ThrusterSettings(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(this, SIGNAL(updateVehicle()),
            this, SLOT(updateThrusterButtons()));

    settingsFile = QApplication::applicationDirPath() + "/settings.ini"; // path to settings file
    settings = new QSettings(settingsFile, QSettings::IniFormat);

    currentVehicle = settings->value("currentVehicle").toString();
    updateThrusterButtons();
}

void ThrusterSettings::updateThrusterButtons()
{
    currentVehicle = settings->value("currentVehicle").toString();

    //clearWidgets(thrustersVerticalLayout);
    settings->beginGroup("vehicle/" + currentVehicle + "/thrusters");
    foreach (QString name, settings->childGroups()) {
        QString buttonName = settings->value(name).toString();
        QPushButton *button = new QPushButton(buttonName);
        button->setText(buttonName);
        thrustersVerticalLayout->addWidget(button);
    }
    settings->endGroup();

    qDebug () << currentVehicle + " (Thrusters)";
}

void ThrusterSettings::clearWidgets(QLayout *layout)
{
    foreach(QPushButton * button,
            layout->findChildren<QPushButton *>(QString(), Qt::FindDirectChildrenOnly)){
        delete button;
    }
}
