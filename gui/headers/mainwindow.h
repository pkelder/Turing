#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"
#include <QtCore>
#include <QtGui>
#include "stateitem.h"
#include "newtransitionwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent * e);
    void CreateTransition(NewTransitionWindow *);
    QList<QPointF> setBestPosition(QPointF,QPointF);
    int getStateNumber();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<StateItem *> state_list;


private slots:
    void on_bouton_clicked();
    void on_StateButton_clicked();
    void on_EditButton_clicked();
    void on_AcceptButton_clicked();
    void on_RejectButton_clicked();
    void on_TransitionButton_clicked();
    void on_DeleteButton_clicked();
    void on_EditTransitionButton_clicked();
    void on_spinBox_valueChanged (int);

};

#endif // MAINWINDOW_H
