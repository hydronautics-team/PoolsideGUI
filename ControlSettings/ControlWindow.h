#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QWidget>
#include "ControlBase.h"

#include "ui_ControlWindow.h"

#include "Control.h"

namespace Ui {
    class ControlWindow;
}

class ControlWindow : public QWidget, public Ui::ControlWindow {
Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();

    Ui::ControlWindow *ui;
//
//public slots:
//    void KeyboardSelection(bool selected);
//    void Mouse3dSelection(bool selected);
//    void JoystickLogitechSelection(bool selected);

private slots:

};

#endif // CONTROLWINDOW_H
