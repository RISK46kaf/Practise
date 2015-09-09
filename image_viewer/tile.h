#ifndef TILE_H
#define TILE_H
#include <QGraphicsPixmapItem>

class Tile : public QGraphicsPixmapItem
{
public:
    Tile(QPixmap i, QPoint p);
    QPoint pnt;
};

#endif // TILE_H
