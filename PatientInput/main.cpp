#include "mainwindow.h"
#include "welcome.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Welcome v;

    v.show();

    MainWindow w;
    //w.show();
    QObject::connect(&v, SIGNAL(auth()),
               &w, SLOT(show()));
    return a.exec();
}
