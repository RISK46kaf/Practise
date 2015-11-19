#include "viewersmanager.h"
#include "MyViewers/mygraphicsview.h"
#include "MyViewers/tilemap.h"
#include "MyViewers/tile.h"
#include "Figures/figuresmanager.h"

#include <QHBoxLayout>
#include <QXmlStreamAttributes>
#include <QScrollBar>
#include <QTimer>
#include <QWidget>
#include <QFileDialog>

using namespace Core;
using namespace MyViewers;
using namespace Figures;

ViewersManager::ViewersManager(QHBoxLayout *layout, QWidget *holder, QObject *parent) : QObject(parent)
{
    _holder = holder;
    _layoutView = layout;
    _scale = 1;
    _figuresManager = new FiguresManager(this);
    _figuresManager->setScalePointer(&_scale);
    _view = new MyGraphicsView(_figuresManager,_holder);
    _view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    _view->setStyleSheet( "QGraphicsView { border-style: none; }" );
    _view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    _layoutView->addWidget(_view);
    _map = NULL;
    _scene = new QGraphicsScene();
    _cmpScene = new QGraphicsScene();
    _t = new QTimer();
    _t->start(60000);
    _map = new TileMap();
    _map->setScene(_scene);
    _oldValueHorizontal = 0;
    _oldValueVertical = 0;
    _view->setScene(_scene);
    _view->verticalScrollBar()->setSingleStep(1);
//    preview->setScale(1);
}

QRect ViewersManager::getViewField()
{
    QRect view_field;
    view_field.setTopLeft(_view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(_view->mapToScene(_view->size().width(),_view->size().height()).toPoint());
    return view_field;
}

QPoint ViewersManager::getCentralPoint()
{
    QRect view_field;
    view_field.setTopLeft(_view->mapToScene(0,0).toPoint());
    view_field.setBottomRight(_view->mapToScene(_view->size().width(),_view->size().height()).toPoint());
    return view_field.topLeft();
}

void ViewersManager::setXML(QString path)
{
    connect(_view, SIGNAL(resized()),this,SLOT(viewResized()));
    connect(_view->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledVertical(int)));
    connect(_view->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(calcDy(int)));
    connect(_view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrolledHorizontal(int)));
    connect(_view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(calcDx(int)));
    connect(_view, SIGNAL(zoomOut(QPoint)),this,SLOT(zoomOut(QPoint)));
    connect(_view, SIGNAL(zoomIn(QPoint)),this,SLOT(zoomIn(QPoint)));
    connect(_t, SIGNAL(timeout()),this,SLOT(timeout()));

    QXmlStreamAttributes att;

    QFile* file = new QFile(path);
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
                _imgSizes.push_back(isize);

                if(att[3].name().toString() == "tile_amount_w")
                {
                    tsize.setWidth(att[3].value().toInt());
                }
                if(att[4].name().toString() == "tile_amount_h")
                {
                    tsize.setHeight(att[4].value().toInt());
                }
                _tileAmount.push_back(tsize);
            }


        }
    }

    _map->setScale(_tileAmount[0],_scale);
    _map->drawViewField(getViewField());
}

void ViewersManager::setMousePos(QPoint pnt)
{
    QCursor c = _holder->cursor();
    c.setPos(_holder->mapToGlobal(pnt));
    _holder->setCursor(c);
}

void ViewersManager::on_actionLoad_Image()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(_holder,tr("Open"),tr(""),tr("Files(*.xml)"));
    if(!fileName.isEmpty())
    {
        _figuresManager->clear();
        QDir d(fileName);
        d.cd("../");
        QString s = d.path();
        _map->loadImage(d);
        setXML(fileName);
    }
    //    setPreview(d.path()+QString("/Preview/1_10.png"));
}

void ViewersManager::viewResized()
{
    emit viewRect(getViewField());
    emit topLeftPointEvent(getCentralPoint());

    _view->verticalScrollBar()->setSingleStep(1);
    _map->drawViewField(getViewField());

    _scene->setSceneRect(0,0,_imgSizes[_scale-1].width(),_imgSizes[_scale-1].height());
}

void ViewersManager::viewChanged()
{
    ///
}

void ViewersManager::scrolledVertical(int value)
{
    emit viewRect(getViewField());
    emit topLeftPointEvent(getCentralPoint());

    _view->horizontalScrollBar()->blockSignals(true);


    _map->drawViewField(getViewField());

    _oldValueVertical = value;
    _view->horizontalScrollBar()->blockSignals(false);
}

void ViewersManager::scrolledHorizontal(int value)
{
    emit viewRect(getViewField());
    emit topLeftPointEvent(getCentralPoint());
    _view->horizontalScrollBar()->blockSignals(true);


    _map->drawViewField(getViewField());
    _view->horizontalScrollBar()->blockSignals(false);
}

void ViewersManager::zoomOut(QPoint pnt)
{
    QPoint npnt = _view->mapToScene(pnt).toPoint();
    if((int)_scale < (_tileAmount.size()))
    {
        qreal x = (qreal)_scale*npnt.x()/(_scale+1);
        qreal y = (qreal)_scale*npnt.y()/(_scale+1);
        ++_scale;
        _map->setScale(_tileAmount[_scale-1],_scale);
        _map->drawViewField(getViewField());
        _scene->setSceneRect(0,0,_imgSizes[_scale-1].width(),_imgSizes[_scale-1].height());
        _view->centerOn(x,y);
        emit viewRect(getViewField());
        emit topLeftPointEvent(getCentralPoint());
    }
}

void ViewersManager::zoomIn(QPoint pnt)
{
    QPoint npnt = _view->mapToScene(pnt).toPoint();
    if((int)_scale > 1)
    {
        qreal x = (qreal)_scale*npnt.x()/(_scale-1);
        qreal y = (qreal)_scale*npnt.y()/(_scale-1);
        --_scale;
        _map->setScale(_tileAmount[_scale-1],_scale);
        _map->drawViewField(getViewField());
        _scene->setSceneRect(0,0,_imgSizes[_scale-1].width(),_imgSizes[_scale-1].height());
        _view->centerOn(x,y);
        emit viewRect(getViewField());
        emit topLeftPointEvent(getCentralPoint());
    }
}

void ViewersManager::timeout()
{
    _map->drawField(10,10,getCentralPoint());
}

void ViewersManager::setViewPos(QPointF pnt)
{
    _view->centerOn(pnt);
}

void ViewersManager::calcDx(int newVal)
{
    _figuresManager->calcDx(newVal);
}

void ViewersManager::calcDy(int newVal)
{
    _figuresManager->calcDy(newVal);
}

void ViewersManager::on_imageListWidget_currentRowChanged(int currentRow)
{
    _cmpScene->clear();
    _cmpScene->addPixmap(QPixmap(_imageList[currentRow]));
}

FiguresManager *ViewersManager::figuresManager()
{
    return _figuresManager;
}

