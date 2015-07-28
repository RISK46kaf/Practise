#include "tilemap.h"


TileMap::TileMap(QObject *parent) :
    QObject(parent)
{
    map_size = QSize(40,18);
    tile_size = QSize(256,256);
    result_size = QSize(3,3);
    resultRect = QRect(QPoint(0,0),QPoint(tile_size.width()*result_size.width(), tile_size.height()*result_size.height()));
    resultRect.center();
}

TileMap::TileMap(QStringList img_paths)
{

}

void TileMap::load(QStringList img_paths)
{
    paths = img_paths;
}

void TileMap::update()
{
    centralTile = QPoint(centralPoint.x()/map_size.width(), centralPoint.y()/map_size.height());
}

void TileMap::viewSizeChanged(QSize size)
{
    view_size = size;
}

void TileMap::centralPointChanged(QPointF pnt)
{
    qDebug()<<centralPoint;
}

uint TileMap::coordinatesToIndex(QPoint pnt)
{
    int x = pnt.x()/tile_size.width();
    int y = pnt.y()/tile_size.height();
    int index = x+y*map_size.width();
    return index;
}



TileMap::~TileMap()
{

}


