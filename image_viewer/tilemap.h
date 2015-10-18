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
#ifdef Q_OS_WIN32
#include <windows.h>
#endif
#include <QDir>

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
    void loadImage(QDir p);
private:
    QSize view_size;
    QSize tile_size;
    QSize map_size;
    QSize result_size;
    QRect rect;
    QGraphicsScene* scene;
    uint scale;
    QString image_path;
};

#endif // TILEMAP_H
