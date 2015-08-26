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
#ifdef WIN32
#include <windows.h>
#endif

class TileMap: public QObject
{
    Q_OBJECT
public:
    explicit TileMap(QObject *parent = 0);
    //explicit TileMap(QGraphicsScene* s);
    QQueue<Tile*> storage;
    QVector<QVector<bool> > matrix;

    void drawTop(QRect r);
    void drawBottom(QRect r);
    void drawRight(QRect r);
    void drawLeft(QRect r);
    void drawViewField(QRect r);
    void drawFromToRight(QRect from, QRect to);
    void drawFromToLeft(QRect from, QRect to);
    void init();
    void setScene(QGraphicsScene *s);
    void setScale(QSize size, uint s);
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
    uint scale;

};

#endif // TILEMAP_H
