#ifndef TILEMAP_H
#define TILEMAP_H
#include <QImage>
#include <QStringList>
#include <QObject>
#include <QDebug>
#include "tile.h"
#include <QQueue>
#include <QGraphicsScene>
#include <QStack>
#include <QVector>
#include <QString>
#include <windows.h>


class TileMap: public QObject
{
    Q_OBJECT
public:
    explicit TileMap(QObject *parent = 0);
    explicit TileMap(QGraphicsScene* s);

    QQueue<Tile*> storage;
    QVector<QVector<bool> > matrix;

    void drawTop(QRect r);
    void drawBottom(QRect r);
    void drawRight(QRect r);
    void drawLeft(QRect r);
    void drawViewField(QRect r);
    void drawFromToRight(QRect from, QRect to);
    void init();
    void setScene(QGraphicsScene *s);
    void viewSizeChanged(QRect r);
    void clear(QRect r);
    void clearAll();
    ~TileMap();
private:
    QSize view_size;
    QSize tile_size;
    QSize map_size;
    QSize result_size;
    QRect rect;
    QGraphicsScene* scene;

};

#endif // TILEMAP_H
