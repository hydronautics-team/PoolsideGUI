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

public slots:
    void KeyboardSelection(int state);
    void Mouse3dSelection(int state);
    void JoystickLogitechSelection(int state);

signals:
    void controllersEnabelChanged(Control::e_controllerType controllerType, bool enabel);

};

#endif // CONTROLWINDOW_H
