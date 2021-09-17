#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QMainWindow>
#include <QTimer>
#include <QtDebug>
#include <QObject>

#include "controlbase.h"
#include "SFML/Window.hpp"

class Keyboard : public ControlBase {
Q_OBJECT

public:
    Keyboard(QString name, int update_time);

private:
    QTimer *update_timer;

    struct control_buttons {
        sf::Keyboard::Key Key;
        int antagonist;
        double setterValue;
        e_actionTypes action;
    };
    const static control_buttons buttons_table[];

private slots:
    void updateKeyboard();

};

#endif // KEYBOARD_H
