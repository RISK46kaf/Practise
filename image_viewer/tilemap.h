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
    //explicit TileMap(QGraphicsScene* s);
    QList<Tile*> storage;
    QVector<QVector<bool> > matrix;

    void drawField(uint width, uint height, QPoint center);
    void drawViewField(QRect r);
    void init();
    void setScene(QGraphicsScene *s);
    void setScale(QSize &size, uint s);
    void viewSizeChanged(QRect r);
    void clear(QRect r);
    void clearAll();
    ~TileMap();
    int memStatus();
private:
    QSize view_size;
    QSize tile_size;
    QSize map_size;
    QSize result_size;
    QRect rect;
    QGraphicsScene* scene;
    uint scale;

};

#endif // TILEMAP_H
