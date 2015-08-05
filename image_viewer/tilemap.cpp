#include "tilemap.h"

TileMap::TileMap(QObject *parent) :
    QObject(parent)
{
    map_size = QSize(40,18);
    tile_size = QSize(256,256);
    result_size = QSize(3,3);
    rect = QRect(QPoint(0,0),QPoint(3,0));
    qDebug()<<rect;
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

Tile TileMap::makeTile(QPoint pnt)
{
    QPixmap pix;
    pix.load(getPath(pnt),"JPEG");
    return Tile(pix,pnt);
}

void TileMap::drawUp(QRect r)
{
    qDebug()<<"draw UP";
    if((r.top()>=0)&&(r.bottom()<map_size.height()*256))
    {
        if(r.top()<((rect.top())*256))
        {
            qDebug()<<"addTop";
            addTop();
        }
        if(r.bottom()<((rect.bottom())*256))
        {
            qDebug()<<"deleteBottom";
            deleteBottom();
        }
    }
}

void TileMap::drawDown(QRect r)
{
    qDebug()<<"drawDown";

    if((r.top()>=0)&&(r.bottom()<map_size.height()*256))
    {
        if(r.bottom()>(rect.bottom()*256))
        {
            qDebug()<<"addBottom";
            addBottom();
        }
        if(r.top()>((rect.top())*256))
        {
            qDebug()<<"deleteTop";
            deleteTop();
        }
    }
}


void TileMap::drawRight(QRect r) /////////////////////
{
/*
    qDebug()<<"r left: "<<r.left()/256;
    qDebug()<<"r right: "<<r.right()/256;
    qDebug()<<"rect left: "<<rect.left();
    qDebug()<<"rect right: "<<rect.right(); */

    qDebug()<<"drawRight";

    if((r.left()>=0)&&(r.right()<map_size.width()*256))
    {
        if(r.right()>(rect.right()*256))
        {
            qDebug()<<"addRight";
            addRight();
        }
        if(r.left()>((rect.left())*256))
        {
            qDebug()<<"deleteLeft";
            deleteLeft();
        }
    }
}

void TileMap::drawLeft(QRect r)
{
    qDebug()<<"drawLeft";

    if((r.left()>=0)&&(r.right()<map_size.width()*256))
    {
        if(r.left()<((rect.left())*256))
        {
            qDebug()<<"addLeft";
            addLeft();
        }
        if(r.right()<((rect.right())*256))
        {
            qDebug()<<"deleteRight";
            deleteRight();
        }
    }
}

/*
void TileMap::viewFieldChanged(QRect r)
{

    qDebug()<<"r top: "<<r.top()/256;
    qDebug()<<"r bottom: "<<r.bottom()/256;
    qDebug()<<"rect top: "<<rect.top();
    qDebug()<<"rect bottom: "<<rect.bottom();

    if((r.top()>=0)&&(r.bottom()<map_size.height()*256))
    {
        if(r.bottom()>(rect.bottom()*256))
        {
            addBottom();
        }
        if(r.bottom()<((rect.bottom()-1)*256))
        {
            deleteBottom();
        }
        if(r.top()<(rect.top()*256))
        {
            addTop();
        }
        if(r.top()>=((rect.top()+2)*256))
        {
            deleteTop();
        }
    }
}
*/
void TileMap::update()
{
}

void TileMap::init()
{
    addBottom();
    addBottom();
    addBottom();
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
    qDebug()<<rect;
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
    qDebug()<<rect; ////////////////////////////////////////////

}

void TileMap::addTop()
{
    QList<Tile*> strip;
    qDebug()<<rect;
    for(uint x=rect.left();x<rect.right();++x)
    {
        QPixmap pix;
        pix.load(getPath(QPoint(x,rect.top())),"JPEG");
        Tile* t = new Tile(pix,QPoint(x,rect.top()));
        strip.push_back(t);

        scene->addItem(strip.last()->img);
    }
    storage.push_front(strip);
    rect.setTop(rect.top()-1);
    qDebug()<<rect; ////////////////////////////////////////////

}

void TileMap::deleteBottom()
{
    for(uint x=0;x<storage[storage.size()-1].size();++x)
    {
        scene->removeItem(storage[storage.size()-1][x]->img);
        delete storage[storage.size()-1][x];
    }
    storage.removeLast();
    rect.setBottom(rect.bottom()-1);
}

void TileMap::deleteTop()
{
    for(uint x=0;x<storage[0].size();++x)
    {
        scene->removeItem(storage[0][x]->img);
        delete storage[0][x];
    }
    storage.removeFirst();
    rect.setTop(rect.top()+1);
}

void TileMap::addRight()
{
    for(uint y=0;y<storage.size();++y)
    {
        QPixmap pix;
        pix.load(getPath(QPoint(rect.right(),y)),"JPEG");
        Tile* t = new Tile(pix,QPoint(rect.right(),y));
        storage[y].push_back(t);
        scene->addItem(storage[y].last()->img);
    }
    rect.setRight(rect.right()+1);
}

void TileMap::addLeft()
{

    for(uint y=0;y<storage.size();++y)
    {
        QPixmap pix;
        pix.load(getPath(QPoint(rect.left(),y)),"JPEG");
        Tile* t = new Tile(pix,QPoint(rect.left(),y));
        storage[y].push_front(t);
        scene->addItem(storage[y].first()->img);
    }
    rect.setLeft(rect.left()-1);
}

void TileMap::deleteRight()
{
    for(uint y=0;y<storage.size();++y)
    {
        scene->removeItem(storage[y].last()->img);
        delete storage[y].last();
        storage[y].removeLast();
    }
    rect.setRight(rect.right()-1);
}

void TileMap::deleteLeft()
{
    for(uint y=0;y<storage.size();++y)
    {
        qDebug()<<"storage "<<storage[y][0];
        scene->removeItem(storage[y].first()->img);
        delete storage[y].first();
        storage[y].removeFirst();
    }
    qDebug()<<"end";
    rect.setLeft(rect.left()+1);
}

QString TileMap::getPath(QPoint pnt)
{
    return paths[pnt.x()+pnt.y()*map_size.width()];
}



TileMap::~TileMap()
{

}

void TileMap::viewSizeChanged(QRect r)
{
    uint width = r.size().width()/256;
    uint height = r.size().height()/256;
    for(uint x=0;x<width;++x)
        addBottom();
    for(uint y=0;y<height;++y)
        addRight();
}
