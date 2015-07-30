#include "tilemap.h"

TileMap::TileMap(QObject *parent) :
    QObject(parent)
{
    map_size = QSize(40,18);
    tile_size = QSize(256,256);
    result_size = QSize(3,3);
    rect = QRect(QPoint(0,0),QPoint(3,0));
}

TileMap::TileMap(QStringList img_paths, QGraphicsScene *scene)
{

}

void TileMap::setScene(QGraphicsScene *s)
{
    scene = s;
}



void TileMap::load(QStringList img_paths)
{
    paths = img_paths;
}

Tile TileMap::madeTile(QPoint pnt)
{
    QPixmap pix;
    pix.load(getPath(pnt),"JPEG");
    return Tile(pix,pnt);
}

void TileMap::update()
{
}

void TileMap::init()
{
    addBottom();
    addBottom();
    addBottom();
    deleteBottom();
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

void TileMap::addBottom()
{
    QList<Tile*> strip;
    for(uint x=rect.left();x<rect.right();++x)
    {
        QPixmap pix;
        pix.load(getPath(QPoint(x,rect.bottom())),"JPEG");
        Tile* t = new Tile(pix,QPoint(x,rect.bottom()));
        strip.push_back(t);

        scene->addItem(strip.last()->img);
    }
    storage.push_back(strip);
    rect.setBottom(rect.bottom()+1);
}

void TileMap::deleteBottom()
{
    for(uint x=0;x<storage[storage.size()-1].size();++x)
    {
        scene->removeItem(storage[storage.size()-1][x]->img);
        delete storage[storage.size()-1][x];

    }
}



QString TileMap::getPath(QPoint pnt)
{
    return paths[pnt.x()+pnt.y()*map_size.width()];
}



TileMap::~TileMap()
{

}


