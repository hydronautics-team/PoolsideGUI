#ifndef THRUSTER_H
#define THRUSTER_H

#include <QWidget>

namespace Ui {
    class Thruster;
}

class Thruster : public QWidget {
Q_OBJECT

public:
    explicit Thruster(QWidget *parent = nullptr);

    ~Thruster();

private:
    Ui::Thruster *ui;
};

#endif // THRUSTER_H
