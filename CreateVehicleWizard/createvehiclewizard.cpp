#include "createvehiclewizard.h"
#include <QSettings>
#include <QFileInfo>
#include <QDebug>

CreateVehicleWizard::CreateVehicleWizard(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    idle = new QState();
    setName = new QState();
    setParameters = new QState();
    finish = new QFinalState();

    connect(btnNext, SIGNAL(clicked()), SIGNAL(nextPressed()));
    connect(btnBack, SIGNAL(clicked()), SIGNAL(backPressed()));
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
    //qDebug () << QApplication::applicationDirPath();
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

void CreateVehicleWizard::startStateMachine()
{
    stateMachine.start();
}

void CreateVehicleWizard::closeEvent(QCloseEvent *event)
{
    stateMachine.stop();
    event->accept();
}

void CreateVehicleWizard::finishWizard()
{
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("vehicle");
    settings.beginGroup(vehicleName->text());
    settings.setValue("name", vehicleName->text());

    settings.beginGroup("configuration");
    settings.setValue("ROV", checkBoxROV->isChecked());
    settings.setValue("AUV", checkBoxAUV->isChecked());
    settings.endGroup();

    /*
    settings.beginGroup("thrusters");
    for (int i = 0; thrusters_count; i++){
        QString number = QString::number(thrusters_count);
        QString name = thrustersTable->item(i,0)->text();
        if (name == "")
            name = number;
        else {
            settings.beginGroup(number);
            settings.setValue("name", name);
            settings.endGroup();
        }
    }
    settings.endGroup();
    */

    settings.endGroup();
    settings.endGroup();

    this->close();
}

void CreateVehicleWizard::updateThrustersCount()
{
    thrusters_count = thrustersSpinBox->value();
    thrustersTable->setRowCount(thrusters_count);
}
