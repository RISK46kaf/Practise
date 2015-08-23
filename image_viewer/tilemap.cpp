#include "tilemap.h"


inline void memStatus()
{
#ifdef WIN32
    MEMORYSTATUSEX statex;

    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);
    //qDebug()<<statex.dwMemoryLoad;
#endif
}



TileMap::TileMap(QObject *parent) :
    QObject(parent)
{
    tile_size = QSize(256,256);
    result_size = QSize(3,3);
    rect = QRect(QPoint(0,0),QPoint(3,0));
    qDebug()<<rect;


}

void TileMap::drawTop(QRect r)
{
    if((r.left()>=0)&&(r.right()<map_size.width()*256)&&(r.top()>=0)&&(r.bottom()<map_size.height()*256))
    {
        uint topBorder = r.top()/256;
        uint bottomBorder = r.bottom()/256;
        Q_UNUSED(bottomBorder)
        uint leftBorder = r.left()/256;
        uint rightBorder = r.right()/256 +1;
        uint y = topBorder;
        for(uint x=leftBorder;x<rightBorder;++x)
        {
            if(matrix[y][x] == false)
            {
                qDebug()<<"drawTop"<<"y="<<y<<"x="<<x;
                matrix[y][x] = true;
                QString path = QString::number(scale)+"/"+QString("y=")+QString::number(y)+"x="+QString::number(x)+"_"+".jpeg";
                Tile * t = new Tile(QPixmap(path,"JPEG"),QPoint(x,y));
                storage.push_back(t);
                scene->addItem(storage.last()->img);
            }
        }
        qDebug()<<"#####drawEND";

    }
}

void TileMap::drawBottom(QRect r)
{
    if((r.left()>=0)&&(r.right()<map_size.width()*256)&&(r.top()>=0)&&(r.bottom()<map_size.height()*256))
    {
        uint topBorder = r.top()/256;
        Q_UNUSED(topBorder)
        uint bottomBorder = r.bottom()/256;
        uint leftBorder = r.left()/256;
        uint rightBorder = r.right()/256 +1;
        uint y = bottomBorder;
        for(uint x=leftBorder;x<rightBorder;++x)
        {
            if(matrix[y][x] == false)
            {
                qDebug()<<"drawBottom"<<"y="<<y<<"x="<<x;
                matrix[y][x] = true;
                QString path = QString::number(scale)+"/"+QString("y=")+QString::number(y)+"x="+QString::number(x)+"_"+".jpeg";
                Tile * t = new Tile(QPixmap(path,"JPEG"),QPoint(x,y));
                storage.push_back(t);
                scene->addItem(storage.last()->img);
            }
        }
        qDebug()<<"#####drawEND";
        memStatus();
    }
}

void TileMap::drawRight(QRect r)
{
    if((r.left()>=0)&&(r.right()<map_size.width()*256)&&(r.top()>=0)&&(r.bottom()<map_size.height()*256))
    {
        uint topBorder = r.top()/256;
        uint bottomBorder = r.bottom()/256+1;
        uint leftBorder = r.left()/256;
        Q_UNUSED(leftBorder)
        uint rightBorder = r.right()/256;
        uint x = rightBorder;
        for(uint y=topBorder;y<bottomBorder;++y)
        {
            if(matrix[y][x] == false)
            {
                qDebug()<<"drawRight"<<"y="<<y<<"x="<<x;
                matrix[y][x] = true;
                QString path = QString::number(scale)+"/"+QString("y=")+QString::number(y)+"x="+QString::number(x)+"_"+".jpeg";
                Tile * t = new Tile(QPixmap(path,"JPEG"),QPoint(x,y));
                storage.push_back(t);
                scene->addItem(storage.last()->img);
            }
        }
    }
    qDebug()<<"#####drawEND";

    memStatus();
}

void TileMap::drawLeft(QRect r)
{
    if((r.left()>=0)&&(r.right()<map_size.width()*256)&&(r.top()>=0)&&(r.bottom()<map_size.height()*256))
    {
        uint topBorder = r.top()/256;
        uint bottomBorder = r.bottom()/256+1;
        uint leftBorder = r.left()/256;
        uint rightBorder = r.right()/256;
        Q_UNUSED(rightBorder)
        uint x = leftBorder;
        for(uint y=topBorder;y<bottomBorder;++y)
        {
            if(matrix[y][x] == false)
            {
                qDebug()<<"drawLeft"<<"y="<<y<<"x="<<x;
                matrix[y][x] = true;
                QString path = QString::number(scale)+"/"+QString("y=")+QString::number(y)+"x="+QString::number(x)+"_"+".jpeg";
                Tile * t = new Tile(QPixmap(path,"JPEG"),QPoint(x,y));
                storage.push_back(t);
                scene->addItem(storage.last()->img);
            }
        }
        qDebug()<<"#####drawEND";
    }
    memStatus();
}

void TileMap::drawViewField(QRect r)
{
    if((r.top()>=0)&&(r.bottom()<map_size.height()*256))
    {
        uint topBorder = r.top()/256;
        uint bottomBorder = r.bottom()/256 +1;
        uint leftBorder = r.left()/256;
        uint rightBorder = r.right()/256 +1;
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
                    scene->addItem(storage.last()->img);
                }
            }
        }
    }
}

void TileMap::drawFromToRight(QRect from, QRect to)
{
    if((to.left()>=0)&&(to.right()<map_size.width()*256))
    {
        uint topBorder = from.top()/256;
        uint bottomBorder = from.bottom()/256 +1;
        uint leftBorder = from.left()/256;
        uint rightBorder = to.right()/256 +1;
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
                    scene->addItem(storage.last()->img);
                }
            }
        }
    }
}

void TileMap::setScene(QGraphicsScene *s)
{
    scene = s;
}

void TileMap::setScale(QSize size, uint s)
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
                scene->removeItem(storage.first()->img);
                delete storage.first();
                storage.removeFirst();
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

}
