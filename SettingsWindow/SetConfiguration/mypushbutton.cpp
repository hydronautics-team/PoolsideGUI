#include "mypushbutton.h"

MyPushButton::MyPushButton()
{
    connect(this, &MyPushButton::clicked, this, &MyPushButton::clicked_To_myCliked);
}

MyPushButton::~MyPushButton()
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void MyPushButton::clicked_To_myCliked()
{
    this->setEnabled(false);
    emit my_clicked(this);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
