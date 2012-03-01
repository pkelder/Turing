#ifndef NEWTRANSITIONWINDOW_H
#define NEWTRANSITIONWINDOW_H

#include <QDialog>

namespace Ui {
class NewTransitionWindow;
}

class NewTransitionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewTransitionWindow(QWidget *parent = 0);
    ~NewTransitionWindow();
    QString getSrc();
    QString getDest();
    QString getRead();
    QString getWrite();
    QString getCursorMv();

private:
    Ui::NewTransitionWindow *ui;
    QString src,dest;
    QString read,write;
    QString cursor_mv;


private slots:
    void on_buttonBox_accepted();
};

#endif // NEWTRANSITIONWINDOW_H
