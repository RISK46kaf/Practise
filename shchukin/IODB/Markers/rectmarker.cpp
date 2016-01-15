#include "rectmarker.h"

RectMarker::RectMarker()
{

}

void RectMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pn;
    pn.setColor(color);
    pn.setWidth(width/currentScale);
    painter->setPen(pn);
    QRect rect;
    rect.setTopLeft(firstPoint);
    rect.setBottomRight(secondPoint);
    painter->drawRect(rect);

}

QRectF RectMarker::boundingRect() const
{
    return QRectF(QPoint(firstPoint),QPoint(secondPoint));
}

QPainterPath RectMarker::shape() const{
    QPainterPath ret;
    ret.addRect(QRectF(QPoint(firstPoint),QPoint(secondPoint)));
    return ret;
}
