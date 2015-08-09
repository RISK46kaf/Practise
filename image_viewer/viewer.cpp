#include "viewer.h"
#include "ui_viewer.h"
#include <QXmlStreamStringRef>

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
    //connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewChanged()));
    connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledVertical(int)));
    connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledHorizontal(int)));

    scale = 1;

    //
    //XML
    QXmlStreamAttributes att;
    QFile* file = new QFile("image.xml");
    if (file->open(QIODevice::ReadOnly))
    {

        QXmlStreamReader xml(file);
        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            att = xml.attributes();
            for(uint i=0;i<att.size();++i)
            {
                qDebug()<<att[i].name().toString();
                qDebug()<<att[i].value().toString();
            }

        }
    }
    //
    scene->setSceneRect(0,0,40*256,18*256);


    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());

    map = new TileMap();
    map->setScene(scene);
    map->drawViewField(view_field);

    view->horizontalScrollBar()->setSingleStep(5);
    oldValueHorizontal = 0;
    oldValueVertical = 0;
    //view->horizontalScrollBar()->setMouseTracking(false);
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
    //paths = QFileDialog::getOpenFileNames(this,tr("Open"),tr(""),tr("Files(*.jpg *.jpeg)"));
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    map->clear(view_field);

}

void Viewer::viewResized()
{
    qDebug()<<"Размер MyGraphicsView:";
    qDebug()<<view->size();
    qDebug()<<"Размер QGraphicsScene:";
    qDebug()<<scene->sceneRect();
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    map->drawViewField(view_field);

}

void Viewer::viewChanged()
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
}

void Viewer::scrolledVertical(int value)
{
    view->horizontalScrollBar()->blockSignals(true);
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());

    if(oldValueVertical > value) //up
    {
        map->drawTop(view_field);
    }
    if(oldValueVertical < value) //down
    {
        map->drawBottom(view_field);
    }
    oldValueVertical = value;
    view->horizontalScrollBar()->blockSignals(false);
}

void Viewer::scrolledHorizontal(int value)
{
    view->horizontalScrollBar()->blockSignals(true);
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    qDebug()<<value;

    if(oldValueHorizontal < value) //right
    {
        if((oldValueHorizontal+256) < value)
        {
            map->drawFromToRight(old_view_field, view_field);
        }
        else
        {
            map->drawRight(view_field);
        }
    }
    if(oldValueHorizontal > value) //left
    {
        map->drawLeft(view_field);
    }
    oldValueHorizontal = value;
    old_view_field = view_field;
    view->horizontalScrollBar()->blockSignals(false);
}


