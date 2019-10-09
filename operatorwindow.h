#ifndef OPERATORWINDOW_H
#define OPERATORWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class OperatorWIndow; }
QT_END_NAMESPACE

class OperatorWindow : public QWidget
{
    Q_OBJECT

public:
    OperatorWindow(QWidget *parent = nullptr);
    ~OperatorWindow();

private:
    Ui::OperatorWIndow *ui;
};
#endif // OPERATORWINDOW_H
