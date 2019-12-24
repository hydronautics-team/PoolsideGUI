#include "rovmodewidget.h"
#include <QDebug>

ROVModeWidget::ROVModeWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    qDebug () << " - ROVModeWidget constructor";
}
