#include "viewer.h"
#include "ui_viewer.h"
#include <QtGui>
#include <QXmlStreamStringRef>
#include "Preview/rectitem.h"
//#include <QSizePolicy>
#include "Figures/figuresmanager.h"

inline void sortSize(QVector<QSize>& sizeList)
{
    for(uint j=1;j<sizeList.size();++j)
    {
        uint key = sizeList[j].width()*sizeList[j].height();
        QSize sk = sizeList[j];
        int i = j - 1;
        while((i > 0)&&((sizeList[i].width()*sizeList[i].height()) < key))
        {
            sizeList[i+1] = sizeList[i];
            i = i - 1;
        }
        sizeList[i+1] = sk;
    }
}


Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
    ui->frame->setLayout(ui->verticalLayout);
    map = NULL;
    view = new MyGraphicsView();
    scene = new MyGraphicsScene();
    preview = new PreviewView();
    cmpScene = new QGraphicsScene();
    ui->gridLayout->addWidget(view);
    ui->previewLayout->addWidget(preview);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setStyleSheet( "QGraphicsView { border-style: none; }" );
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //view->setDragMode(QGraphicsView::ScrollHandDrag);
    scale = 1;

    //cmp

    cmpView = new MyGraphicsView();
    cmpScene = new QGraphicsScene();
    cmpPreview = new PreviewView();
    cmpView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    cmpView->setStyleSheet( "QGraphicsView { border-style: none; }" );
    cmpView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    cmpView->setDragMode(QGraphicsView::ScrollHandDrag);

    cmpScale = 1;

    ui->compareLayout->addWidget(cmpPreview);
    ui->compareLayout->addWidget(cmpView);



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

    t = new QTimer();
    t->start(60000);


    map = new TileMap();

    map->setScene(scene);
    map->setView(view);
    map->setPreviewView(preview);

    cmpMap = new TileMap();

    cmpMap->setScene(cmpScene);
    cmpMap->setView(cmpView);
    cmpMap->setPreviewView(cmpPreview);
    //map->setScale(tileAmount[0],scale);
    //map->drawViewField(getViewField());

    oldValueHorizontal = 0;
    oldValueVertical = 0;
    view->setScene(scene);
    view->verticalScrollBar()->setSingleStep(1);

    cmpView->setScene(cmpScene);
    cmpView->verticalScrollBar()->setSingleStep(1);
    preview->setScale(1);
    //view->verticalScrollBar()->setMaximumHeight(4352);

}

Viewer::~Viewer()
{
    delete map;
    delete scene;
    delete view;
    delete t;
    //delete preview;
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

    //
    connect(view, SIGNAL(resized()),map,SLOT(viewResized()));
    //connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewChanged()));
    connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), map, SLOT(scrolledVertical(int)));
    connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), map, SLOT(scrolledHorizontal(int)));
    connect(view, SIGNAL(zoomOut(QPoint)),map,SLOT(zoomOut(QPoint)));
    connect(view, SIGNAL(zoomIn(QPoint)),map,SLOT(zoomIn(QPoint)));
    connect(t, SIGNAL(timeout()),map,SLOT(timeout()));
    connect(map, SIGNAL(viewRect(QRect)), preview, SLOT(setR(QRect)));
    connect(map, SIGNAL(topLeftPointEvent(QPointF)), preview, SLOT(setP(QPointF)));

    connect(map,SIGNAL(scaleChanged(uint)),this,SLOT(markerScaleChange(uint)));

    //connect(this,SIGNAL(viewRect(QRect r)),preview->getRectItem(),SLOT());

    //    if(map == NULL)
    //        return;
    //    map->clear(getViewField());
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open"),tr(""),tr("Files(*.xml)"));
    QDir d(fileName);
    d.cd("../");
    QString p = d.path();
    map->loadImage(d);

    preview->setImage(d.path()+QString("/Preview/1_10.png"));

    QXmlStreamAttributes att;

    QVector<QSize> imgSizes;
    QVector<QSize> tileAmount;


    QFile* file = new QFile(fileName);
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
    }

    sortSize(imgSizes);
    sortSize(tileAmount);
    preview->setMaxScale(imgSizes.size()-1);
    map->setScale(tileAmount[0],scale);
    map->setImgSizes(imgSizes);
    map->setTileAmount(tileAmount);
    map->drawViewField(getViewField());
}





void Viewer::timeout()
{
    map->drawField(10,10,getCentralPoint());
}

void Viewer::setViewPos(QPointF pnt)
{
    view->centerOn(pnt);
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
    return view_field.topLeft();
}

void Viewer::setXML(QString path)
{



}

void Viewer::setPreview(QString path)
{
    preview->setImage(path);
}

void Viewer::setMousePos(QPoint pnt)
{
    QCursor c = cursor();
    c.setPos(mapToGlobal(pnt));
    setCursor(c);
}

void Viewer::markerScaleChange(uint sc)
{
    scale = sc;
    for(uint i=0;i<markers.size();++i)
    {
        QTransform tr;
        double a = 1.0/sc;
        tr.scale(a,a);
        markers[i]->item->setTransform(tr);
    }
}


void Viewer::on_imageListWidget_currentRowChanged(int currentRow)
{
    cmpScene->clear();
    cmpScene->addPixmap(QPixmap(imageList[currentRow]));
}

void Viewer::on_actionLoad_Images_2_triggered()
{
    //
    connect(cmpView, SIGNAL(resized()),cmpMap,SLOT(viewResized()));
    //connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewChanged()));
    connect(cmpView->verticalScrollBar(), SIGNAL(valueChanged(int)), cmpMap, SLOT(scrolledVertical(int)));
    connect(cmpView->horizontalScrollBar(), SIGNAL(valueChanged(int)), cmpMap, SLOT(scrolledHorizontal(int)));
    connect(cmpView, SIGNAL(zoomOut(QPoint)),cmpMap,SLOT(zoomOut(QPoint)));
    connect(cmpView, SIGNAL(zoomIn(QPoint)),cmpMap,SLOT(zoomIn(QPoint)));



    connect(t, SIGNAL(timeout()),cmpMap,SLOT(timeout()));
    connect(cmpMap, SIGNAL(viewRect(QRect)), cmpPreview, SLOT(setR(QRect)));
    connect(cmpMap, SIGNAL(topLeftPointEvent(QPointF)), cmpPreview, SLOT(setP(QPointF)));
    //connect(this,SIGNAL(viewRect(QRect r)),preview->getRectItem(),SLOT());

    QXmlStreamAttributes att;
    QVector<QSize> imgSizes;
    QVector<QSize> tileAmount;

    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open"),tr(""),tr("Files(*.xml)"));
    QDir d(fileName);
    d.cd("../");
    QString p = d.path();
    cmpMap->loadImage(d);

    cmpPreview->setImage(d.path()+QString("/Preview/1_10.png"));


    QFile* file = new QFile(fileName);
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
    }
    sortSize(imgSizes);
    sortSize(tileAmount);
    cmpPreview->setMaxScale(imgSizes.size()-1);

    cmpMap->setScale(tileAmount[0],scale);
    cmpMap->setImgSizes(imgSizes);
    cmpMap->setTileAmount(tileAmount);
    cmpMap->drawViewField(getViewField());
}


void Viewer::on_arrowButton_clicked()
{
    Marker* m = new Marker();

    connect(scene, SIGNAL(mousePressPos(QPoint)),m,SLOT(setFirstPoint(QPoint)));
    connect(scene, SIGNAL(mouseReleasePos(QPoint)),m,SLOT(setScecondPoint(QPoint)));

    m->drawArrow();
    scene->addItem(m->item);
    m->item->setZValue(2);
    markers.push_back(m);
    m->item->update();
}
