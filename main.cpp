#include "operatorwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OperatorWindow w;
    w.show();
    return a.exec();
}
