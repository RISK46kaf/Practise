#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
    view = new MyGraphicsView();
    scene = new QGraphicsScene();
    ui->gridLayout->addWidget(view);
    view->setScene(scene);
    view->setStyleSheet( "QGraphicsView { border-style: none; }" );
    connect(view, SIGNAL(resized()),this,SLOT(viewResized()));
    connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewChanged()));
    connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewChanged()));
}

Viewer::~Viewer()
{
    delete ui;
    for(uint i=0;i<items.size();++i)
        delete items[i];
}

void Viewer::on_actionPrepare_Image_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open"),tr(""),tr("Files(*.jpeg *.jpg)"));
    QImage img(fileName);
    cutter.cut(fileName);
}

void Viewer::on_actionLoad_Images_triggered()
{
    QStringList paths = QFileDialog::getOpenFileNames(this,tr("Open"),tr(""),tr("Files(*.jpg *.jpeg)"));
/*
    for(uint i=0;i<paths.size();++i)
    {
        QPixmap pix;
        pix.load(paths[i],"JPEG");
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pix);
        items.push_back(pixmapItem);
        pixmapItem->setPos(0,i*256);
        scene->addItem(pixmapItem);
    }
*/
    scene->setSceneRect(0,0,40*256,18*256);
    map = new TileMap();
    connect(this, SIGNAL(centralPointEvent(QPointF)), map, SLOT(centralPointChanged(QPointF)));
    centralItem = new QGraphicsPixmapItem();
    map->load(paths);
    scene->addItem(centralItem);
    drawTiles(paths,QSize(10,10));
}

void Viewer::viewResized()
{
    qDebug()<<"Размер MyGraphicsView:";
    qDebug()<<view->size();
    qDebug()<<"Размер QGraphicsScene:";
    qDebug()<<scene->sceneRect();
    qDebug()<<"Центр:";
    QPointF pnt = view->mapToScene(QPoint(view->size().width()/2,view->size().height()/2)); //Координаты центра видимой области
    qDebug()<<pnt;

}

void Viewer::viewChanged()
{

    QPointF pnt = view->mapToScene(QPoint(0,0)); //Координаты центра видимой области

    emit centralPointEvent(pnt);

    QPixmap pix;
    pix.load(map->centralPath,"JPEG");

    //centralItem->setPixmap(pix);
    //centralItem->setPos(view->mapToScene(QPoint(0,0)));
    qDebug()<<pnt;
}


void Viewer::drawTiles(QStringList paths, QSize size)
{
    for(uint y=0;y<size.height();++y)
    {
        for(uint x=0;x<size.width();++x)
        {
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
            items.push_back(item);
            QPixmap pix;
            pix.load(paths[x+y*size.width()],"JPEG");
            item->setPixmap(pix);
            item->moveBy(x*256,y*256);
            scene->addItem(item);
        }
    }
}
