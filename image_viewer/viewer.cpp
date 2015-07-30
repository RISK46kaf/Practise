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
    delete scene;
    delete view;
    delete map;
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
    paths = QFileDialog::getOpenFileNames(this,tr("Open"),tr(""),tr("Files(*.jpg *.jpeg)"));

    scene->setSceneRect(0,0,40*256,18*256);
    map = new TileMap();
    connect(this, SIGNAL(centralPointEvent(QPointF)), map, SLOT(centralPointChanged(QPointF)));
    centralItem = new QGraphicsPixmapItem();
    map->load(paths);
    map->setScene(scene);
    map->init();

}

void Viewer::viewResized()
{
    qDebug()<<"Размер MyGraphicsView:";
    qDebug()<<view->size();
    qDebug()<<"Размер QGraphicsScene:";
    qDebug()<<scene->sceneRect();
    qDebug()<<"Центр:";
    QPointF pnt = view->mapToScene(QPoint(view->size().width()/2,view->size().height()/2)); //Координаты центра видимой области

}

void Viewer::viewChanged()
{

}


void Viewer::drawTiles(QStringList paths, QSize size)
{

}



void Viewer::createBottomStrip(QStringList paths, QSize size)
{

}
