#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT

public:
    MyPushButton();
    ~MyPushButton();

public slots:
    void clicked_To_myCliked();

signals:
    void my_clicked(MyPushButton*);
};

#endif // MYPUSHBUTTON_H
