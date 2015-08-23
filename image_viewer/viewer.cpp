#include "viewer.h"
#include "ui_viewer.h"
#include <QXmlStreamStringRef>
//#include <QSizePolicy>
#include "Figures/figuresmanager.h"

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

    scale = 1;

//    Rect r;
//    Ellipse* ptr = (Ellipse*)r.toEllipse();

//    qDebug() << ptr->getFigureType() << ptr;

//    delete ptr;
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
            Q_UNUSED(token)  // если 'token' используется убрать
            att = xml.attributes();
            if(att.size() != 0)
            {
                QSize size;
                if(att[1].name().toString() == "width")
                {
                    size.setWidth(att[1].value().toInt());
                }
                if(att[2].name().toString() == "height")
                {
                    size.setHeight(att[2].value().toInt());
                }
                qDebug()<<size;
                scaleList.push_back(size);
            }

        }
        //
        scene->setSceneRect(0,0,scaleList[0].width()*256,scaleList[0].height()*256);


        map = new TileMap();
        map->setScene(scene);
        map->setScale(scaleList[0],scale);
        map->drawViewField(getViewField());

        view->horizontalScrollBar()->setSingleStep(5);
        oldValueHorizontal = 0;
        oldValueVertical = 0;
        //view->horizontalScrollBar()->setMouseTracking(false);
    }
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
    map->clear(getViewField());
}

void Viewer::viewResized()
{
    qDebug()<<"Размер MyGraphicsView:";
    qDebug()<<view->size();
    qDebug()<<"Размер QGraphicsScene:";
    qDebug()<<scene->sceneRect();

    map->drawViewField(getViewField());

}

void Viewer::viewChanged()
{

}

void Viewer::scrolledVertical(int value)
{
    view->horizontalScrollBar()->blockSignals(true);


    if((int)oldValueVertical > value) //up
    {
        map->drawTop(getViewField());
    }
    if((int)oldValueVertical < value) //down
    {
        map->drawBottom(getViewField());
    }
    oldValueVertical = value;
    view->horizontalScrollBar()->blockSignals(false);
}

void Viewer::scrolledHorizontal(int value)
{
    view->horizontalScrollBar()->blockSignals(true);

    qDebug()<<value;


    if((int)oldValueHorizontal < value) //right
    {
        if((int)(oldValueHorizontal+256) < value)
        {
            map->drawFromToRight(old_view_field, getViewField());
        }
        else
        {
            map->drawRight(getViewField());
        }
    }
    if((int)oldValueHorizontal > value) //left
    {
        map->drawLeft(getViewField());
    }
    oldValueHorizontal = value;
    old_view_field = getViewField();
    view->horizontalScrollBar()->blockSignals(false);
}



void Viewer::on_zoomOutButton_clicked()
{
    if((int)scale < (scaleList.size()))
    {
        ++scale;
        map->setScale(scaleList[scale-1],scale);
        map->drawViewField(getViewField());
        scene->setSceneRect(0,0,scaleList[0].width()*256,scaleList[0].height()*256);
    }
}

QRect Viewer::getViewField()
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    return view_field;
}

QPoint Viewer::getCentralPoint()
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    return view_field.center();
}

