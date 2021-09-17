#ifndef COMMUNICATIONSETTINGS_H
#define COMMUNICATIONSETTINGS_H

#include "ui_communicationsettings.h"

class CommunicationSettings : public QWidget, private Ui::CommunicationSettings {
Q_OBJECT

public:
    explicit CommunicationSettings(QWidget *parent = nullptr);
};

#endif // COMMUNICATIONSETTINGS_H
