#ifndef TILEMAP_H
#define TILEMAP_H
#include <QImage>
#include <QStringList>
#include <QObject>
#include <QDebug>

class TileMap: public QObject
{
    Q_OBJECT
public:
    explicit TileMap(QObject *parent = 0);
    explicit TileMap(QStringList img_paths);

    void setCentralPoint(QPoint pnt);
    QString getResult(QPoint pnt);
    void setMapSize(QSize size);
    void setTileSize(QSize size);
    void load(QStringList img_paths);

    QStringList paths;
    QStringList result;

    QPoint centralTile;
    QString centralPath;
    QPoint centralPoint;

    ~TileMap();
private:
    QSize view_size;
    QSize tile_size;
    QSize map_size;
    QRect resultRect;
    QSize result_size;

    void update();
    uint coordinatesToIndex(QPoint pnt);
public slots:
    void viewSizeChanged(QSize size);
    void centralPointChanged(QPointF pnt);
};

#endif // TILEMAP_H
