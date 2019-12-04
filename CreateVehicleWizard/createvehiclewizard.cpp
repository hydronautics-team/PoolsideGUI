#include "createvehiclewizard.h"

CreateVehicleWizard::CreateVehicleWizard(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(btnNext, SIGNAL(clicked()), SIGNAL(NextPressed()));
    connect(btnBack, SIGNAL(clicked()), SIGNAL(BackPressed()));
    connect(btnExit, SIGNAL(clicked()), SIGNAL(ExitPressed()));

    idle = new QState();
    setName = new QState();
    setParameters = new QState();
    exit = new QState();

    idle->addTransition(this, SIGNAL(NextPressed()), setName);
    idle->addTransition(this, SIGNAL(ExitPressed()), exit);

    setName->addTransition(this, SIGNAL(NextPressed()), setParameters);
    setName->addTransition(this, SIGNAL(BackPressed()), idle);
    setName->addTransition(this, SIGNAL(ExitPressed()), exit);

    idle->assignProperty(stackedWidget,"currentIndex", "0");
    idle->assignProperty(btnBack, "enabled", "False");

    setName->assignProperty(stackedWidget,"currentIndex", "1");
    setName->assignProperty(btnBack, "enabled", "True");


    stateMachine.addState(idle);
    stateMachine.addState(setName);
    stateMachine.addState(exit);

    stateMachine.setInitialState(idle);

    stateMachine.start();
}
