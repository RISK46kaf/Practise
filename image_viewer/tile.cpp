#include "tile.h"

Tile::Tile()
{
}


Tile::Tile(QPixmap i, QPoint p)
{
    img = new QGraphicsPixmapItem();
    img->setPixmap(i);
    img->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    img->setPos(256*p.x(),256*p.y());
    pnt = p;
}

Tile::~Tile()
{
    delete img;
}
