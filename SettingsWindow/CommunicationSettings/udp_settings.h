#ifndef UDP_SETTINGS_H
#define UDP_SETTINGS_H

#include "ui_udp_settings.h"

#include <QWidget>

class UDP_Settings : public QWidget, private Ui::UDP_Settings {
Q_OBJECT

public:
    explicit UDP_Settings(QWidget *parent = nullptr);

    ~UDP_Settings();
};

#endif // UDP_SETTINGS_H
