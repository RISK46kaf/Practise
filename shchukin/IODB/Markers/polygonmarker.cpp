#include "polygonmarker.h"

PolygonMarker::PolygonMarker()
{

}

void PolygonMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pn;
    pn.setColor(color);
    pn.setWidth(width/currentScale);
    painter->setPen(pn);
    painter->drawPolygon(poly);
    painter->drawPoint(points.last());

}

QRectF PolygonMarker::boundingRect() const
{
    return QRectF(poly.boundingRect());
}

QPainterPath PolygonMarker::shape() const
{
    QPainterPath ret;
    ret.addRect(poly.boundingRect());
    return ret;
}
