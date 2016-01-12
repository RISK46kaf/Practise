#include "imagewidget.h"

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

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    map = NULL;
    view = new MyGraphicsView();
    scene = new MyGraphicsScene();
    preview = new PreviewView();
    layout = new QGridLayout(this);
    openButton = new QPushButton("Открыть изображение", this);
//    layout->addWidget(openButton,0,1);
    layout->addWidget(preview,0,0);
    subLayout = new QVBoxLayout(this);
    comenLab = new QLabel("Краткий комментарий об изображении");
    comenLab->setMaximumHeight(21);
    comenLab->setAlignment(Qt::AlignCenter);
    textComen = new QTextEdit();
    //
    subLayout->addWidget(openButton);
    subLayout->addWidget(comenLab);
    subLayout->addWidget(textComen);
    layout->addLayout(subLayout,0,1);
    layout->addWidget(view,1,0,1,0,0);
//    layout->addWidget(view,1,0,1,0,1);
    connect(openButton,SIGNAL(clicked(bool)),this,SLOT(openImage(bool)));
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setStyleSheet( "QGraphicsView { border-style: none; }" );
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->setMinimumWidth(1000);
    //view->setDragMode(QGraphicsView::ScrollHandDrag);
    scale = 1;

    map = new TileMap();

    map->setScene(scene);
    map->setView(view);
    map->setPreviewView(preview);

    oldValueHorizontal = 0;
    oldValueVertical = 0;
    view->setScene(scene);
    view->verticalScrollBar()->setSingleStep(1);

    comenLab->setMaximumHeight(21);
    openButton->setMaximumHeight(21);
    textComen->setMaximumHeight(preview->height()
                                - comenLab->height() - openButton->height());
//    textComen->setMinimumWidth();
    openButton->setMaximumWidth(textComen->width());
    preview->setScale(1);
}

void ImageWidget::openByName(const QString &path)
{
    filename = path + "/image.xml";
    qDebug() << "filename 777" << filename;
    QDir d(filename);
    d.cd("../");
    QString p = d.path();
    map->loadImage(d);

    QDir dirry (path+"/Preview/");

    qDebug() << d.path();
//    path = d.path();
    QStringList sList;
    qDebug() << "fucking" << (sList = dirry.entryList(QDir::Files | QDir::NoDotAndDotDot));

    if(sList.count())
    {
        qDebug() << dirry.path() + "/" + sList.last();
    preview->setImage(dirry.path() + "/" + sList.last());
    }

    QXmlStreamAttributes att;

    QVector<QSize> imgSizes;
    QVector<QSize> tileAmount;


    QFile* file = new QFile(filename);
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
    preview->setOriginalSize(imgSizes[0]);
    preview->setMaxScale(imgSizes.size()-1);
    scale = tileAmount.count();
    qDebug() << "SCAAAAALEEE "<< scale;
    map->setScale(tileAmount.last(),scale);
    map->setImgSizes(imgSizes);
    map->setTileAmount(tileAmount);
    map->drawViewField(getViewField());
}

QString ImageWidget::getFilename() const
{
    return filename;
}

QString ImageWidget::getPath() const
{
    return path;
}

void ImageWidget::openImage(bool)
{
    connect(view, SIGNAL(resized()),map,SLOT(viewResized()));
    connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), map, SLOT(scrolledVertical(int)));
    connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), map, SLOT(scrolledHorizontal(int)));
    connect(view, SIGNAL(zoomOut(QPoint)),map,SLOT(zoomOut(QPoint)));
    connect(view, SIGNAL(zoomIn(QPoint)),map,SLOT(zoomIn(QPoint)));
    //connect(t, SIGNAL(timeout()),map,SLOT(timeout()));
    connect(map, SIGNAL(viewRect(QRect)), preview, SLOT(setR(QRect)));
    connect(map, SIGNAL(topLeftPointEvent(QPointF)), preview, SLOT(setP(QPointF)));
    connect(map,SIGNAL(scaleChanged(uint)),this,SLOT(markerScaleChange(uint)));

    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open"),tr(""),tr("Files(*.xml)"));

    if(!QFileInfo(fileName).exists())
        return;
    filename = fileName;
    qDebug() << "filename 777" << filename;
    QDir d(filename);
    d.cd("../");
    path = d.path();
    openByName(path);
}

void ImageWidget::setViewPos(QPointF pnt)
{
    view->centerOn(pnt);
}

QRect ImageWidget::getViewField()
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    for(uint i=0;i<markers.size();++i)
    {
        scene->update(markers[i]->item->sceneBoundingRect());
        view->update();
        markers[i]->item->update();
    }


    return view_field;
}

QPoint ImageWidget::getCentralPoint()
{
    QRect view_field;
    view_field.setTopLeft(view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(view->mapToScene(view->size().width(),view->size().height()).toPoint());
    return view_field.center();
}


void ImageWidget::setPreview(QString path)
{
    preview->setImage(path);
}

void ImageWidget::markerScaleChange(uint sc)
{
    scale = sc;
    for(uint i=0;i<markers.size();++i)
    {
        qDebug()<<"####ImageWidgetScale:#### "<<scale;
        markers[i]->setScale(scale);
    }
}
