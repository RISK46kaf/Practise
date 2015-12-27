#include "tilenameparser.h"
#include "myexception.h"
#include <iostream>

TileNameParser::TileNameParser() : BIG_X("X"), BIG_Y("Y")
{
}

QPair<QPoint, bool> TileNameParser::operator()(const QString &data, const QString &format)
{
//    std::cout << "\npraser start\n";
//    std::cout << data.toStdString() << std::endl;
    QPair<QPoint, bool> retVal;
    int X = format.indexOf(BIG_X);
    int Y = format.indexOf(BIG_Y);
    int dot = data.lastIndexOf(".");
    QString extension = "*" + data.mid(dot);
    bool firstX = X < Y;
//    std::cout << "firstX " << firstX << "\n";
    QString preX = firstX ? format.mid(0,X) :
                            format.mid(Y + BIG_Y.size(),X - (Y + BIG_Y.size()));
    QString preY = firstX ? format.mid(X + BIG_X.size(), Y - (X + BIG_X.size())) :
                            format.mid(0,Y);
    bool ok1 = 0, ok2 = 0;
    int _x, _y;
    if(!firstX)
    {
        QString y = data.mid(preY.size(),data.indexOf(preX) - data.indexOf(preY) - preY.size());
        QString x = data.mid(preX.size() + preY.size() + y.size(),
                              data.size() - (preX.size() + preY.size() + y.size())
                                - extension.size() + 1);
        _x = x.toInt(&ok1);
        _y = y.toInt(&ok2);
//        std::cout << "x " << x.toStdString() << "\n";
//        std::cout << "y " << y.toStdString() << "\n";
    }
    else
    {
        QString x = data.mid(preX.size(),data.indexOf(preY) - data.indexOf(preX) - preX.size());
        QString y = data.mid(preY.size() + preX.size() + x.size(),
                              data.size() - (preY.size() + preX.size() + x.size())
                                - extension.size() + 1);
        _y = y.toInt(&ok1);
        _x = x.toInt(&ok2);
//        std::cout << "x " << x.toStdString() << "\n";
//        std::cout << "y " << y.toStdString() << "\n";
    }
    if(!ok1 || !ok2 /*|| extension != "*" + data.mid(data.lastIndexOf("."))*/)
    {
        std::cout << "Warning! Wrong data to parse "
                    << std::endl;
        retVal = QPair<QPoint, bool>(QPoint(),false);
    }
    else
        retVal = QPair<QPoint, bool>(QPoint(_x,_y), true);
//    std::cout << "praser ends\n\n";
    return retVal;
}

