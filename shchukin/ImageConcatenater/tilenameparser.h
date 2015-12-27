#ifndef TILENAMEPARSER_H
#define TILENAMEPARSER_H

#include <QtCore>


class TileNameParser
{
public:
    TileNameParser();
    QPair<QPoint, bool> operator()(const QString& data, const QString& format);
private:
    const QString BIG_X;
    const QString BIG_Y;
};

#endif // TILENAMEPARSER_H
