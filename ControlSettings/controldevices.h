#ifndef CONTROLDEVICES_H
#define CONTROLDEVICES_H

#include <QWidget>

namespace Ui {
class ControlDevices;
}

class ControlDevices : public QWidget
{
    Q_OBJECT

public:
    explicit ControlDevices(QWidget *parent = nullptr);
    ~ControlDevices();

private slots:
    void on_checkBox_KeyBoard_clicked(bool checked);

    void on_checkBox_3dMouse_clicked(bool checked);

    void on_checkBox_JoystickLogitech_clicked(bool checked);

private:
    Ui::ControlDevices *ui;
};

#endif // CONTROLDEVICES_H
