#ifndef SERIAL_SETTINGS_H
#define SERIAL_SETTINGS_H

#include "ui_serial_settings.h"

#include <QWidget>

class Serial_Settings : public QWidget, private Ui::Serial_Settings
{
    Q_OBJECT

public:
    explicit Serial_Settings(QWidget *parent = nullptr);
    ~Serial_Settings();
};

#endif // SERIAL_SETTINGS_H
