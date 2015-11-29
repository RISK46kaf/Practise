#include "arrowmarker.h"

ArrowMarker::ArrowMarker()
{

}

void ArrowMarker::test()
{
    qDebug()<<"as";
}

void ArrowMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pn;
    pn.setColor(QColor(Qt::green));
    pn.setWidth(20);
    painter->setPen(pn);
    painter->drawLine(firstPoint, secondPoint);
    qDebug()<<"Arrow p1="<<firstPoint<<" p2="<<secondPoint;
}

QRectF ArrowMarker::boundingRect() const
{
    return QRectF(firstPoint, secondPoint);
}
