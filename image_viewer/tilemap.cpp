#include "tilemap.h"


int TileMap::memStatus()
{
    MEMORYSTATUSEX statex;

    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);
    qDebug()<<statex.dwMemoryLoad;
    qDebug()<<sizeof(statex.dwMemoryLoad);
    qDebug()<<sizeof(int);

    return statex.dwMemoryLoad;
}



TileMap::TileMap(QObject *parent) :
    QObject(parent)
{
    tile_size = QSize(256,256);
    result_size = QSize(3,3);
    rect = QRect(QPoint(0,0),QPoint(3,0));
    map_size = QSize(0,0);
}

void TileMap::drawField(uint width, uint height, QPoint center)
{
    QPoint c(center.x()/256,center.y()/256);
    for(uint y=(height/256)-(c.y()/2);y<(height/256)+(c.y()/2);++y)
    {
        for(uint x=(width/256)+(c.x()/2);x<(width/256)+(c.x()/2);++x)
        {
            if(matrix[y][x] == false)
            {
                matrix[y][x] = true;
                QString path = QString::number(scale)+"/"+QString("y=")+QString::number(y)+"x="+QString::number(x)+"_"+".jpeg";
                Tile * t = new Tile(QPixmap(path,"JPEG"),QPoint(x,y));
                storage.push_back(t);
                scene->addItem(storage.last());
            }
        }
    }
}



void TileMap::drawViewField(QRect r)
{

    if(((r.bottom()/256) <= map_size.height())&&((r.right()/256) <= map_size.width()))
    {
        uint topBorder = r.top()/256;
        uint bottomBorder = r.bottom()/256 +1;
        uint leftBorder = r.left()/256;
        uint rightBorder = r.right()/256 +1;
        if((rightBorder-1) == map_size.width())
            --rightBorder;
        if((bottomBorder-1) == map_size.height())
            --bottomBorder;
        for(uint y=topBorder;y<bottomBorder;++y)
        {
            for(uint x=leftBorder;x<rightBorder;++x)
            {
                if(matrix[y][x] == false)
                {
                    matrix[y][x] = true;
                    QString path = QString::number(scale)+"/"+QString("y=")+QString::number(y)+"x="+QString::number(x)+"_"+".jpeg";
                    Tile * t = new Tile(QPixmap(path,"JPEG"),QPoint(x,y));
                    storage.push_back(t);
                    scene->addItem(storage.last());
                }
            }
        }
    }

    if(memStatus() > 80)
    {
        clear(r);
    }

}


void TileMap::setScene(QGraphicsScene *s)
{
    scene = s;
}

void TileMap::setScale(QSize& size, uint s)
{
    for(int i=0;i<matrix.size();++i)
        matrix[i].clear();
    matrix.clear();
    map_size = size;
    scale = s;
    for(int y=0;y<map_size.height();++y)
    {
        QVector<bool> v;
        matrix.push_back(v);
        for(int x=0;x<map_size.width();++x)
        {
            matrix[y].push_back(0);
        }
    }
}

void TileMap::clear(QRect r)
{
    int topBorder = r.top()/256;
    int bottomBorder = r.bottom()/256;
    int leftBorder = r.left()/256;
    int rightBorder = r.right()/256 ;
    qDebug()<<"storage size: "<<storage.size();

    for(int y=0;y<map_size.height();++y)
    {
        for(int x=0;x<map_size.width();++x)
        {
            if((matrix[y][x] == true)&&(((y<topBorder)||(y>bottomBorder))||((x<leftBorder)||(x>rightBorder))))
            {
//                scene->removeItem(storage.first());
//                delete storage.first();
//                storage.removeFirst();
                scene->removeItem(storage[y*map_size.width()+x]);
                storage.removeAt(y*map_size.width()+x);
                matrix[y][x] = false;
            }
        }
    }
    qDebug()<<"storage size then: "<<storage.size();

    for(int y=0;y<matrix.size();++y)
    {
        QString s;
        for(int x=0;x<matrix[y].size();++x)
        {
            s += QString::number(matrix[y][x]);
        }
        qDebug()<<s;
    }
}




TileMap::~TileMap()
{
    for(uint i=0;i<storage.size();++i)
    {
        delete storage[i];
    }
}
