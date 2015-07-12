#include "markingtools.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MarkingTools w;
    w.show();

    return a.exec();
}
