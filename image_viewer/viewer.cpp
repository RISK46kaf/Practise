#include "viewer.h"
#include "ui_viewer.h"
#include <QtGui>
#include <QXmlStreamStringRef>
//#include <QSizePolicy>
#include "Figures/figures.h"

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
    view->setStyleSheet( "QGraphicsView { border-style: none; }" );
    connect(view, SIGNAL(resized()),this,SLOT(viewResized()));
    //connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewChanged()));
    connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledVertical(int)));
    connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledHorizontal(int)));

    scale = 1;

    Rect r;
    //Ellipse* ptr = (Ellipse*)r.toEllipse();

    //qDebug() << ptr->getFigureType() << ptr;

    //delete ptr;
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


        map = new TileMap();
        map->setScene(scene);
        map->setScale(scaleList[0],scale);
        map->drawViewField(getViewField());

        //view->horizontalScrollBar()->setSingleStep(5);
        //view->setRenderHint(QPainter::Antialiasing, false);

        //view->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
        oldValueHorizontal = 0;
        oldValueVertical = 0;
        view->setScene(scene);
        scene->setSceneRect(0,0,scaleList[0].width()*256,scaleList[0].height()*256);
        //view->horizontalScrollBar()->setMouseTracking(false);
        view->verticalScrollBar()->setSingleStep(1);
        //view->verticalScrollBar()->setMaximumHeight(4352);
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

void Viewer::viewResized()//////////////////////////////
{
    view->verticalScrollBar()->setSingleStep(1);
    //view->verticalScrollBar()->setMaximumHeight(4352);
    qDebug()<<"МАХ скролл-бар: "<<view->verticalScrollBar()->maximum();
    qDebug()<<"Размер MyGraphicsView:";
    qDebug()<<view->size();
    qDebug()<<"Размер QGraphicsScene:";
    qDebug()<<scene->sceneRect();
    map->drawViewField(getViewField());
    view->horizontalScrollBar()->setValue(0);
    view->verticalScrollBar()->setValue(0);
    scene->setSceneRect(0,0,scaleList[0].width()*256,scaleList[0].height()*256);
    view->horizontalScrollBar()->setMaximum((scaleList[0].width())*256);
    uint s  =scaleList[0].height()*256;
    qDebug()<<s;
    int ps = view->verticalScrollBar()->pageStep();
    //view->verticalScrollBar()->setMaximum(4096-ps);
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
    qDebug()<<value;
}

void Viewer::scrolledHorizontal(int value)
{
    view->horizontalScrollBar()->blockSignals(true);

    qDebug()<<value;


    if((int)oldValueHorizontal < value) //right
    {
        if((oldValueHorizontal+256) < value)
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
    if(scale < (scaleList.size()))
    {
        ++scale;
        map->setScale(scaleList[scale-1],scale);
        map->drawViewField(getViewField());
        //scene->setSceneRect(0,0,scaleList[scale-1].width()*256,scaleList[scale-1].height()*256);
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

