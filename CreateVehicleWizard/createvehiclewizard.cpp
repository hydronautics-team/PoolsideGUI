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
    settings.setValue("ROV", checkBoxROV->isChecked());
    settings.setValue("AUV", checkBoxAUV->isChecked());
    settings.endGroup();
    settings.endGroup();

    this->close();
}
