#include "viewer.h"
#include "ui_viewer.h"
#include <QtGui>
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
    view->setStyleSheet( "QGraphicsView { border-style: none; }" );
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scale = 1;

//<<<<<<< HEAD
//    Rect r;
    //Ellipse* ptr = (Ellipse*)r.toEllipse();

    //qDebug() << ptr->getFigureType() << ptr;

    //delete ptr;
//=======
//    Rect r;
//    Ellipse* ptr = (Ellipse*)r.toEllipse();

//    qDebug() << ptr->getFigureType() << ptr;

//    delete ptr;
//>>>>>>> 06aa6648283460898d44a259b9ac63c7c036bed2
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
                QSize isize;
                QSize tsize;
                if(att[1].name().toString() == "width")
                {
                    isize.setWidth(att[1].value().toInt());
                }
                if(att[2].name().toString() == "height")
                {
                    isize.setHeight(att[2].value().toInt());
                }
                imgSizes.push_back(isize);

                if(att[3].name().toString() == "tile_amount_w")
                {
                    tsize.setWidth(att[3].value().toInt());
                }
                if(att[4].name().toString() == "tile_amount_h")
                {
                    tsize.setHeight(att[4].value().toInt());
                }
                tileAmount.push_back(tsize);
            }


        }
        t = new QTimer();
        t->start(60000);

        //
        connect(view, SIGNAL(resized()),this,SLOT(viewResized()));
        //connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewChanged()));
        connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledVertical(int)));
        connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledHorizontal(int)));
        connect(view, SIGNAL(zoomOut(QPoint)),this,SLOT(zoomOut(QPoint)));
        connect(view, SIGNAL(zoomIn(QPoint)),this,SLOT(zoomIn(QPoint)));
        connect(t, SIGNAL(timeout()),this,SLOT(timeout()));

        map = new TileMap();

        map->setScene(scene);
        map->setScale(tileAmount[0],scale);
        map->drawViewField(getViewField());

        oldValueHorizontal = 0;
        oldValueVertical = 0;
        view->setScene(scene);
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
    delete t;
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
    if(map == NULL)
        return;
    map->clear(getViewField());
}

void Viewer::viewResized()//////////////////////////////
{
    view->verticalScrollBar()->setSingleStep(1);
    map->drawViewField(getViewField());
    view->horizontalScrollBar()->setValue(0);
    view->verticalScrollBar()->setValue(0);
    ui->progressBar->setValue(map->memStatus());

    scene->setSceneRect(0,0,imgSizes[scale-1].width(),imgSizes[scale-1].height());
}

void Viewer::viewChanged()
{

}

void Viewer::scrolledVertical(int value)
{
    view->horizontalScrollBar()->blockSignals(true);


    map->drawViewField(getViewField());
    ui->progressBar->setValue(map->memStatus());

    oldValueVertical = value;
    view->horizontalScrollBar()->blockSignals(false);
}

void Viewer::scrolledHorizontal(int value)
{
    view->horizontalScrollBar()->blockSignals(true);

    ui->progressBar->setValue(map->memStatus());

    map->drawViewField(getViewField());
    view->horizontalScrollBar()->blockSignals(false);
}



void Viewer::on_zoomOutButton_clicked()
{
    if((int)scale < (tileAmount.size()))
    {

        ++scale;
        map->setScale(tileAmount[scale-1],scale);
        map->drawViewField(getViewField());
        scene->setSceneRect(0,0,imgSizes[scale-1].width(),imgSizes[scale-1].height());
    }
}

void Viewer::zoomOut(QPoint pnt)
{
    QPoint npnt = view->mapToScene(pnt).toPoint();
    if((int)scale < (tileAmount.size()))
    {
        int x = scale*npnt.x()/(scale+1);
        int y = scale*npnt.y()/(scale+1);
        ++scale;
        map->setScale(tileAmount[scale-1],scale);
        map->drawViewField(getViewField());
        scene->setSceneRect(0,0,imgSizes[scale-1].width(),imgSizes[scale-1].height());
        view->centerOn(QPoint(x,y));

    }
}

void Viewer::zoomIn(QPoint pnt)
{ 
    QPoint npnt = view->mapToScene(pnt).toPoint();
    if((int)scale > 1)
    {
        int x = scale*npnt.x()/(scale-1);
        int y = scale*npnt.y()/(scale-1);
        --scale;
        map->setScale(tileAmount[scale-1],scale);
        map->drawViewField(getViewField());
        scene->setSceneRect(0,0,imgSizes[scale-1].width(),imgSizes[scale-1].height());
        view->centerOn(QPoint(x,y));
    }
}

void Viewer::timeout()
{
    map->drawField(10,10,getCentralPoint());
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

void Viewer::setMousePos(QPoint pnt)
{
    QCursor c = cursor();
    c.setPos(mapToGlobal(pnt));
    setCursor(c);
}


