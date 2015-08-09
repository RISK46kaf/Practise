#include "viewer.h"
#include "ui_viewer.h"
//#include <QSizePolicy>

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
    ui->frame->setLayout(ui->verticalLayout);
    map = NULL;
    view = new MyGraphicsView();
    scene = new QGraphicsScene();
    ui->gridLayout->addWidget(view);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setScene(scene);
    view->setStyleSheet( "QGraphicsView { border-style: none; }" );
    connect(view, SIGNAL(resized()),this,SLOT(viewResized()));
    //connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewChanged()));
    connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledVertical(int)));
    connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledHorizontal(int)));

    l=false;

}

Viewer::~Viewer()
{
    delete map;
    delete scene;
    delete view;
    delete ui;
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
    paths = QFileDialog::getOpenFileNames(this,tr("Open"),tr(""),tr("Files(*.jpg *.jpeg *.png)"));

    scene->setSceneRect(0,0,40*256,18*256);
    if(map != NULL) delete map;
    map = new TileMap();
    connect(this, SIGNAL(centralPointEvent(QPointF)), map, SLOT(centralPointChanged(QPointF)));
    centralItem = new QGraphicsPixmapItem();
    map->load(paths);
    map->setScene(scene);
    map->init();
    l=true;

}

void Viewer::viewResized()
{
    if(l)
    {
    qDebug()<<"Размер MyGraphicsView:";
    qDebug()<<view->size();
    qDebug()<<"Размер QGraphicsScene:";
    qDebug()<<scene->sceneRect();
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    map->viewSizeChanged(view_field);
    }

}

void Viewer::viewChanged()
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    map->viewSizeChanged(view_field);
}

void Viewer::scrolledVertical(int value)
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());

    if((int)oldValueVertical > value) //up
    {
        map->drawUp(view_field);
    }
    if((int)oldValueVertical < value) //down
    {
        map->drawDown(view_field);
    }
    oldValueVertical = value;
}

void Viewer::scrolledHorizontal(int value)
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    if((int)oldValueHorizontal < value) //right
    {
        map->drawRight(view_field);
    }
    if((int)oldValueHorizontal > value) //left
    {
        map->drawLeft(view_field);
    }
    oldValueHorizontal = value;
}


