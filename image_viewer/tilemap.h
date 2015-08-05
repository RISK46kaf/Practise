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


class TileMap: public QObject
{
    Q_OBJECT
public:
    explicit TileMap(QObject *parent = 0);
    explicit TileMap(QStringList img_paths, QGraphicsScene* scene);

    void setCentralPoint(QPoint pnt);
    QString getResult(QPoint pnt);
    void setMapSize(QSize size);
    void setTileSize(QSize size);
    void setScene(QGraphicsScene* s);
    void load(QStringList img_paths);
    void init();
    Tile makeTile(QPoint pnt);
    //void viewFieldChanged(QRect r);
    void drawUp(QRect r);
    void drawDown(QRect r);
    void drawLeft(QRect r);
    void drawRight(QRect r);

    void viewSizeChanged(QRect r);

    QGraphicsScene* scene;
    QStringList paths;
    QList<QList<Tile*> > storage;

    QPoint centralTile;
    QString centralPath;
    QPoint centralPoint;

    ~TileMap();
private:
    QSize view_size;
    QSize tile_size;
    QSize map_size;
    QSize result_size;
    QRect rect;


    void update();
    uint coordinatesToIndex(QPoint pnt);
    void addBottom();
    void addTop();
    void deleteBottom();
    void deleteTop();
    void addRight();
    void deleteRight();
    QString getPath(QPoint pnt);
    void deleteLeft();
    void addLeft();
public slots:
    void centralPointChanged(QPointF pnt);
};

#endif // TILEMAP_H
