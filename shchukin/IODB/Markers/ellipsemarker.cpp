#include "ellipsemarker.h"

EllipseMarker::EllipseMarker()
{

}

void EllipseMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    painter->drawEllipse(rect);

}

QRectF EllipseMarker::boundingRect() const
{
    return QRectF(QPoint(firstPoint),QPoint(secondPoint));
}

QPainterPath EllipseMarker::shape() const{
    QPainterPath ret;
    ret.addRect(QRectF(QPoint(firstPoint),QPoint(secondPoint)));
    return ret;
}
