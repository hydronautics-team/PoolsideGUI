#ifndef OPERATORWINDOW_H
#define OPERATORWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class OperatorWindow; }
QT_END_NAMESPACE

class OperatorWindow : public QWidget
{
    Q_OBJECT

public:
    OperatorWindow(QWidget *parent = nullptr);
    ~OperatorWindow();

private:
    Ui::OperatorWindow *ui;
};
#endif // OPERATORWINDOW_H
