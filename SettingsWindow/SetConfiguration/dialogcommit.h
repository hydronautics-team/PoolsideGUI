#ifndef DIALOGCOMMIT_H
#define DIALOGCOMMIT_H

#include <QWidget>

namespace Ui {
class DialogCommit;
}

class DialogCommit : public QWidget
{
    Q_OBJECT

public:
    explicit DialogCommit(QWidget *parent = nullptr);
    ~DialogCommit();

private:
    Ui::DialogCommit *ui;
};

#endif // DIALOGCOMMIT_H
