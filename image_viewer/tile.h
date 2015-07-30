#ifndef TILE_H
#define TILE_H
#include <QGraphicsPixmapItem>

struct Tile
{
    Tile();
    Tile(QPixmap i, QPoint p);
    QGraphicsPixmapItem* img;
    QPoint pnt;
    ~Tile();
};

#endif // TILE_H
