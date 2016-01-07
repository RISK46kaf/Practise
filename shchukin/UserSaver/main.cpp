#include "usersaver.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserSaver w;
    w.show();

    return a.exec();
}
