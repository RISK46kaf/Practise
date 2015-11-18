#include "tilemap.h"
#ifdef Q_OS_UNIX
#include <QProcess>
#endif

int TileMap::memStatus()
{
    int memPercent;
#ifdef Q_OS_WIN32
    MEMORYSTATUSEX statex;

    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);
    qDebug()<<statex.dwMemoryLoad;
    qDebug()<<sizeof(statex.dwMemoryLoad);
    qDebug()<<sizeof(int);
    memPercent = statex.dwMemoryLoad;
#endif
#ifdef Q_OS_OSX
    QProcess p;
    QString virtualMem, memSize;
    p.start("sysctl", QStringList() << "hw.physmem");
    p.waitForFinished();
    virtualMem = p.readAllStandardOutput();
    p.close();
    p.start("sysctl", QStringList() << "hw.memsize");
    p.waitForFinished();
    memSize = p.readAllStandardOutput();
    p.close();
    virtualMem = virtualMem.remove(0,virtualMem.indexOf(":")+2);
    memSize = memSize.remove(0,memSize.indexOf(":")+2);
    memPercent = 100*(virtualMem.toDouble()/memSize.toDouble());
#endif
#ifdef Q_OS_LINUX
    //    QProcess p;
    //    QString virtualMem, memSize;
    //    p.start("sysctl", QStringList() << "hw.physmem");
    //    p.waitForFinished();
    //    virtualMem = p.readAllStandardOutput();
    //    p.close();
    //    p.start("sysctl", QStringList() << "hw.memsize");
    //    p.waitForFinished();
    //    memSize = p.readAllStandardOutput();
    //    p.close();
    //    memPercent = virtualMem.toDouble()/memSize.toDouble();
    //    free | awk \'\/buffers\\/cache\/{printf(\", %.2f%\"), $4/($3+$4)*100}\'
    //            awk '/MemTotal/ {print $2}' /proc/meminfo
    memPercent = 100
        #endif
            return memPercent;
}

void TileMap::loadImage(QDir p)
{
    image_path = p.path() + "/";
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
                QString path = image_path + QString::number(scale)+"/"+QString("y=")+QString::number(y)+"x="+QString::number(x)+".png";
                Tile * t = new Tile(QPixmap(path,"PNG"),QPoint(x,y));
                storage.push_back(t);
                scene->addItem(storage.last());
            }
        }
    }
}



void TileMap::drawViewField(QRect r)
{

    if(memStatus() > 85)
    {
        clearAll();
    }
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
                    QString path = image_path +  QString::number(scale)+"/"+QString("y=")+QString::number(y)+"x="+QString::number(x)+".png";
                    Tile * t = new Tile(QPixmap(path,"PNG"),QPoint(x,y));
                    storage.push_back(t);
                    scene->addItem(storage.last());
                }
            }
        }
    }
}


void TileMap::setScene(QGraphicsScene *s)
{
    scene = s;
}

void TileMap::setView(QGraphicsView *v)
{
    view = v;
}

void TileMap::setPreviewView(PreviewView *pv)
{
    preview = pv;
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

void TileMap::setImgSizes(QVector<QSize> ims)
{
    imgSizes = ims;
}

void TileMap::setTileAmount(QVector<QSize> ta)
{
    tileAmount = ta;
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

void TileMap::clearAll()
{
    qDebug()<<"storage size: "<<storage.size();
    for(uint i=0;i<storage.size();++i)
        delete storage[i];
    storage.clear();
    qDebug()<<"storage size then: "<<storage.size();
    for(int y=0;y<matrix.size();++y)
    {
        for(int x=0;x<matrix[y].size();++x)
        {
            matrix[y][x] = 0;
        }
    }
}



void TileMap::viewResized()
{
    emit viewRect(getViewField());
    emit topLeftPointEvent(getCentralPoint());

    view->verticalScrollBar()->setSingleStep(1);
    this->drawViewField(getViewField());


    scene->setSceneRect(0,0,imgSizes[scale-1].width(),imgSizes[scale-1].height());
}

void TileMap::scrolledVertical(int value)
{
    emit viewRect(getViewField());
    emit topLeftPointEvent(getCentralPoint());

    view->horizontalScrollBar()->blockSignals(true);


    this->drawViewField(getViewField());

    //oldValueVertical = value;
    view->horizontalScrollBar()->blockSignals(false);
}

void TileMap::scrolledHorizontal(int value)
{
    emit viewRect(getViewField());
    emit topLeftPointEvent(getCentralPoint());
    view->horizontalScrollBar()->blockSignals(true);


    this->drawViewField(getViewField());
    view->horizontalScrollBar()->blockSignals(false);
}

void TileMap::zoomOut(QPoint pnt)
{
    QPoint npnt = view->mapToScene(pnt).toPoint();
    QPoint c = view->mapToScene(view->size().width()/2,view->size().height()/2).toPoint();

    int d1 = qSqrt(qPow(npnt.x() - c.x(),2) + qPow(npnt.y() - c.y(),2));
    if((int)scale < (tileAmount.size()))
    {
        clearAll();

        int x = scale*npnt.x()/(scale+1);
        int y = scale*npnt.y()/(scale+1);

        int px = scale*c.x()/(scale+1);//центр
        int py = scale*c.y()/(scale+1);

        int d2 = qSqrt(qPow(x - px,2) + qPow(y - py,2));


        ++scale;
        this->setScale(tileAmount[scale-1],scale);
        this->drawViewField(getViewField());
        scene->setSceneRect(0,0,imgSizes[scale-1].width(),imgSizes[scale-1].height());
        preview->setScale(scale);

        emit viewRect(getViewField());
        emit topLeftPointEvent(getCentralPoint());



        if((x>px)&&(y>py))
            view->centerOn(QPoint(px+qSqrt(qPow(x-px,2))/scale,py+qSqrt(qPow(y-py,2))/scale));
        if((x>px)&&(y<py))
            view->centerOn(QPoint(px+qSqrt(qPow(x-px,2))/scale,py-qSqrt(qPow(y-py,2))/scale));
        if((x<px)&&(y>py))
            view->centerOn(QPoint(px-qSqrt(qPow(x-px,2))/scale,py+qSqrt(qPow(y-py,2))/scale));
        if((x<px)&&(y<py))
            view->centerOn(QPoint(px-qSqrt(qPow(x-px,2))/scale,py-qSqrt(qPow(y-py,2))/scale));

        scene->update();
        view->update();
    }
}

void TileMap::zoomIn(QPoint pnt)
{
    QPoint npnt = view->mapToScene(pnt).toPoint();
    QPoint c = view->mapToScene(view->size().width()/2,view->size().height()/2).toPoint();

    int d = qSqrt(qPow(pnt.x(),2) + qPow(pnt.y(),2));
    if((int)scale > 1)
    {
        clearAll();

        int x = scale*npnt.x()/(scale-1);
        int y = scale*npnt.y()/(scale-1);

        int px = scale*c.x()/(scale-1);
        int py = scale*c.y()/(scale-1);

        int d2 = qSqrt(qPow(x - px,2) + qPow(y - py,2));



        --scale;
        this->setScale(tileAmount[scale-1],scale);
        this->drawViewField(getViewField());
        scene->setSceneRect(0,0,imgSizes[scale-1].width(),imgSizes[scale-1].height());


        if((x>px)&&(y>py))
            view->centerOn(QPoint(px+qSqrt(qPow(x-px,2))/scale,py+qSqrt(qPow(y-py,2))/scale));
        if((x>px)&&(y<py))
            view->centerOn(QPoint(px+qSqrt(qPow(x-px,2))/scale,py-qSqrt(qPow(y-py,2))/scale));
        if((x<px)&&(y>py))
            view->centerOn(QPoint(px-qSqrt(qPow(x-px,2))/scale,py+qSqrt(qPow(y-py,2))/scale));
        if((x<px)&&(y<py))
            view->centerOn(QPoint(px-qSqrt(qPow(x-px,2))/scale,py-qSqrt(qPow(y-py,2))/scale));


        preview->setScale(scale);
        emit viewRect(getViewField());
        emit topLeftPointEvent(getCentralPoint());

        scene->update();
        view->update();
    }
}




TileMap::~TileMap()
{
    for(uint i=0;i<storage.size();++i)
    {
        delete storage[i];
    }
}


QRect TileMap::getViewField()
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    return view_field;
}

QPoint TileMap::getCentralPoint()
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    return view_field.topLeft();
}
