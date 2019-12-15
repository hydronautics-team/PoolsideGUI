#include "vehiclewizard.h"
#include <QSettings>
#include <QFileInfo>
#include <QDebug>
#include "mainwindow.h"

VehicleWizard::VehicleWizard(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(btnNext, SIGNAL(clicked()), SIGNAL(nextPressed()));
    connect(btnBack, SIGNAL(clicked()), SIGNAL(backPressed()));

    //---------------------------------

    idle = new QState();
    setName = new QState();
    setParameters = new QState();
    finish = new QFinalState();

    connect(&stateMachine, SIGNAL(finished()), SLOT(finishWizard()));

    idle->addTransition(this, SIGNAL(nextPressed()), setName);

    setName->addTransition(this, SIGNAL(nextPressed()), setParameters);
    setName->addTransition(this, SIGNAL(backPressed()), idle);

    setParameters->addTransition(this, SIGNAL(nextPressed()), finish);
    setParameters->addTransition(this, SIGNAL(backPressed()), setName);

    idle->assignProperty(stackedWidget,"currentIndex", "0");
    idle->assignProperty(btnBack, "enabled", "False");
    idle->assignProperty(btnNext, "text", "Next");

    setName->assignProperty(stackedWidget,"currentIndex", "1");
    setName->assignProperty(btnBack, "enabled", "True");
    setName->assignProperty(btnNext, "text", "Next");

    setParameters->assignProperty(stackedWidget,"currentIndex", "2");
    setParameters->assignProperty(btnNext, "text", "Finish");

    stateMachine.addState(idle);
    stateMachine.addState(setName);
    stateMachine.addState(setParameters);
    stateMachine.addState(finish);

    stateMachine.setInitialState(idle);

    //---------------------------------

    connect(thrustersSpinBox, SIGNAL(valueChanged(int)), SLOT(updateThrustersCount()));
    thrustersTable->setColumnCount(1);

    //---------------------------------

    settingsFile = QApplication::applicationDirPath() + "/settings.ini";

    QFile file(settingsFile);
    if(QFileInfo::exists(settingsFile))
    {
        qDebug () << "file exists";
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        qDebug()<<"file already created";
        file.close();
    }
    else
    {
        qDebug () << "file does not exists";
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        qDebug()<<"file created"<<endl;
        file.close();
    }
}

void VehicleWizard::startStateMachine()
{
    stateMachine.start();
}

void VehicleWizard::closeEvent(QCloseEvent *event)
{
    stateMachine.stop();
    event->accept();
}

void VehicleWizard::enableButtonNext()
{

}

void VehicleWizard::enableButtonFinish()
{

}

void VehicleWizard::finishWizard()
{
    // save vehicle in settings.ini
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("vehicle");

    settings.beginGroup(vehicleName->text());
    settings.setValue("name", vehicleName->text());

    settings.beginGroup("configuration");
    settings.setValue("ROV", checkBoxROV->isChecked());
    settings.setValue("AUV", checkBoxAUV->isChecked());
    settings.endGroup();

    settings.beginGroup("thrusters");
    settings.setValue("count", thrusters_count);
    for (int i = 0; i < thrusters_count; i++){
        QString number = QString::number(i);
        QString name;
        if (!thrustersTable->item(i,0))
            name = number;
        else if (thrustersTable->item(i,0)->text().isEmpty()) {
            name = number;
        }
        else
            name = thrustersTable->item(i,0)->text();
        settings.beginGroup(number);
        settings.setValue("name", name);
        settings.endGroup();
    }
    settings.endGroup();

    settings.endGroup();
    settings.endGroup();

    // update chooseVehicle menu
    emit updateMainWindow();

    this->close();
}

void VehicleWizard::updateThrustersCount()
{
    thrusters_count = thrustersSpinBox->value();
    thrustersTable->setRowCount(thrusters_count);
}
