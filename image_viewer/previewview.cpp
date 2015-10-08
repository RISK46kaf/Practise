#include "previewview.h"

PreviewView::PreviewView()
{    
    this->setFixedSize(QSize(500,500));
    scene = new QGraphicsScene();
    this->setScene(scene);
    QPixmap img("5/scale=5.jpeg");
    pixItem.setPixmap(img);
    scene->addItem(&pixItem);
    //scene->addPixmap(img);
    //item.setPixmap(img);
    scene->setSceneRect(0,0,img.width(),img.height());
    rectItem = new RectItem(QRect(0,0,img.width(),img.height()));
    scene->addItem(rectItem);
}

PreviewView::~PreviewView()
{
    delete scene;
}

void PreviewView::setR(QRect r)
{
    qDebug()<<"wdad";
    QPoint p1 = r.topLeft();
    QPoint p2 = r.bottomRight();
    rect.setTopLeft(p1);
    rect.setBottomRight(p2);
    rectItem->setRect(getViewField(r));
    qDebug()<<"r tl"<<r.topLeft();
    qDebug()<<"r br"<<r.bottomRight();
    qDebug()<<"scene br "<<scene->sceneRect().bottomRight();
    qDebug()<<"rect to scene"<<getViewField(r);
    //rectItem->setScale();
    rectItem->setPos(pixItem.mapFromScene(r.topLeft()/5));
    qDebug()<<rectItem->pos();
    //reDraw();
}

void PreviewView::setP(QPointF p)
{   
    rectItem->setPos(pixItem.mapFromScene(p/5));
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

QRect PreviewView::getViewField(QRect in)
{
    QRect view_field;
    view_field.setTopLeft(pixItem.mapToScene(in.topLeft()/5).toPoint());
    view_field.setBottomRight(pixItem.mapToScene(in.bottomRight()/5).toPoint());
    return view_field;
}
