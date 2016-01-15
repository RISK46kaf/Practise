#include "tile.h"


Tile::Tile(QPixmap i, QPoint p)
{
    this->setPixmap(i);
    this->setPos(QPoint(p.x()*256,p.y()*256));
    this->setZValue(1);
    pnt = p;
}

