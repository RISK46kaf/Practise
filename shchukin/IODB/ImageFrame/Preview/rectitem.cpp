#include "rectitem.h"


RectItem::RectItem(QRectF bRect)
{
    setFlags(QGraphicsItem::ItemIsSelectable|
             QGraphicsItem::ItemIsMovable);
    br = bRect;
}

RectItem::~RectItem()
{

}

void RectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pn;
    pn.setColor(QColor(Qt::green));
    pn.setWidth(10/factor);
    painter->setPen(pn);
    painter->drawRect(rect);

}

QRectF RectItem::boundingRect() const
{
    return br;
}

void RectItem::setRect(QRect r)
{
    QPoint p1 = r.topLeft();
    QPoint p2 = r.bottomRight();

    rect.setTopLeft(p1);
    rect.setBottomRight(p2);
    update();
}

void RectItem::setFactor(int f)
{
    factor = f;
}

void RectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    qDebug()<<this->pos();
}
