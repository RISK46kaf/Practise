#include "previewview.h"

PreviewView::PreviewView()
{    
    this->setFixedSize(QSize(250,125));
    scene = new QGraphicsScene();
    this->setScene(scene);
    //QPixmap img("5/scale=5.jpeg");

}

PreviewView::~PreviewView()
{
}

void PreviewView::setR(QRect r)
{
    int p1 = r.size().width()*scale/max_scale;
    int p2 = r.size().height()*scale/max_scale;
    rect.setTopLeft(QPoint(0,0));
    rect.setBottomRight(QPoint(p1,p2));
    rectItem->setRect(getViewField(rect));
    //qDebug()<<"r tl"<<r.topLeft();
    //qDebug()<<"r br"<<r.bottomRight();
    //qDebug()<<"scene br "<<scene->sceneRect().bottomRight();
    //qDebug()<<"rect to scene"<<getViewField(r);
    //rectItem->setScale();
    //rectItem->setPos(pixItem.mapFromScene(r.topLeft()/1));
    //qDebug()<<rectItem->pos();
    //reDraw();
    update();
}

void PreviewView::setP(QPointF p)
{   

    rectItem->setPos(pixItem.mapToScene(p).toPoint()*scale/10);
    //rectItem->setPos(pixItem.mapToScene(rect.topLeft()/(6-scale)).toPoint());
    update();
}

void PreviewView::setScale(uint s)
{
    scale = s;
}


void PreviewView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    this->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
    reDraw();
}

void PreviewView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

}

void PreviewView::reDraw()
{
    qDebug()<<rect.center();
}

RectItem *PreviewView::getRectItem()
{
    return rectItem;
}

void PreviewView::setMaxScale(int max)
{
    max_scale = max;
}

void PreviewView::setImage(QString path)
{
    QPixmap img(path,"JPG");
    pixItem.setPixmap(img);
    scene->addItem(&pixItem);
    //scene->addPixmap(img);
    //item.setPixmap(img);
    scene->setSceneRect(0,0,img.width(),img.height());
    rectItem = new RectItem(QRect(0,0,img.width(),img.height()));
    scene->addItem(rectItem);
}

QRect PreviewView::getViewField(QRect in)
{
    QRect view_field;
    view_field.setTopLeft(pixItem.mapToScene(in.topLeft()).toPoint());
    view_field.setBottomRight(pixItem.mapToScene(in.bottomRight()).toPoint());
    int w = view_field.width();
    int h = view_field.height();
    view_field.setBottomRight(QPoint(w,h));
    //qDebug()<<"scaled rect"<<view_field.bottomRight()/scale;
    //qDebug()<<"SCALE "<<scale;
    return view_field;    
}
