#include "newtransitionwindow.h"
#include "ui_newtransitionwindow.h"
#include "mainwindow.h"

NewTransitionWindow::NewTransitionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTransitionWindow)
{
    ui->setupUi(this);
    int max=((MainWindow *)this->parent())->getStateNumber();
    ui->spinBoxSrc->setRange(1,max);
    ui->spinBoxDest->setRange(1,max);

}

NewTransitionWindow::~NewTransitionWindow()
{

    delete ui;
}

void NewTransitionWindow::on_buttonBox_accepted(){
    read=ui->read->toPlainText();
    write=ui->write->toPlainText();
    cursor_mv=ui->cursor_mv->toPlainText();
    src=QString::number(ui->spinBoxSrc->value());
    dest=QString::number(ui->spinBoxDest->value());

    ((MainWindow *)this->parent())->CreateTransition(this);
}

QString NewTransitionWindow::getSrc(){
    return src;
}

QString NewTransitionWindow::getDest(){
    return dest;
}


QString NewTransitionWindow::getRead(){
    return read;
}

QString NewTransitionWindow::getWrite(){
    return write;
}

QString NewTransitionWindow::getCursorMv(){
    return cursor_mv;
}

