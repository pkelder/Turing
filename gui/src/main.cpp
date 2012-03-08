#include <QtGui/QApplication>
#include "mainwindow.h"
#include <iostream>
#include <string>
/*#include "Simulation.h"
#include "TmParser.h"*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

   return a.exec();
}
