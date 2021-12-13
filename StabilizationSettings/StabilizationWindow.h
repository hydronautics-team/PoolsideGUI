#ifndef STABILIZATIONSETTINGS_H
#define STABILIZATIONSETTINGS_H

#include <QWidget>

namespace Ui {
    class StabilizationWindow;
}

class StabilizationWindow : public QWidget {
Q_OBJECT

public:
    explicit StabilizationWindow(QWidget *parent = nullptr);

    ~StabilizationWindow();

private:
    Ui::StabilizationWindow *ui;
};

#endif // STABILIZATIONSETTINGS_H
