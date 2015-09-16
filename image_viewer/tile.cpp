#include "tile.h"


Tile::Tile(QPixmap i, QPoint p)
{
    this->setPixmap(i);
    this->setPos(QPoint(p.x()*256,p.y()*256));
    pnt = p;
}

