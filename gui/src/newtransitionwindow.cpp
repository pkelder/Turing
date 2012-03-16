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



/**** Methode de fermeture de la fenêtre avec clic sur OK ****/

void NewTransitionWindow::on_buttonBox_accepted(){
   //récupération des données entrées par l'utilisateur
    read=ui->read->toPlainText();
    write=ui->write->toPlainText();
    cursor_mv=ui->cursor_mv->toPlainText();
    src=QString::number(ui->spinBoxSrc->value());
    dest=QString::number(ui->spinBoxDest->value());

    //appel de la méthode de création de transition
    ((MainWindow *)this->parent())->CreateTransition(this);
}



/**** Accesseurs ****/


QString NewTransitionWindow::getSrc() const{
    return src;
}

QString NewTransitionWindow::getDest() const{
    return dest;
}


QString NewTransitionWindow::getRead() const{
    return read;
}

QString NewTransitionWindow::getWrite() const{
    return write;
}

QString NewTransitionWindow::getCursorMv() const{
    return cursor_mv;
}

