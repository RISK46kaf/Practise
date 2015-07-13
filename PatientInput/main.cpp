#include "mainwindow.h"
#include "welcome.h"
#include "finder.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Welcome v;

    v.show();

    MainWindow w;
    //w.show();

    Finder f;

    QObject::connect(&v, SIGNAL(auth_i()),
               &w, SLOT(show()));

    QObject::connect(&v, SIGNAL(auth_f()),
               &f, SLOT(show()));
    return a.exec();
}
