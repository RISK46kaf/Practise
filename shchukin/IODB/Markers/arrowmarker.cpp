#include "arrowmarker.h"
#include <QtMath>


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
    pn.setWidth(20/currentScale);
    painter->setPen(pn);
    painter->drawLine(firstPoint, secondPoint);
   // painter->drawRect(this->boundingRect());

    double PI = 3.14;

    QLineF line;

    line.setP1(firstPoint);
    line.setP2(secondPoint);

    qDebug()<<"angle "<<line.angle();

    //double angle = std::acos(line().dx() / line().length());

    //double ang  = double(line.angle());

    double ang = std::acos(line.dx() / line.length());

    qreal arrowSize = 100;
    /*
    if (line.dy() >= 0)
        ang = (PI * 2) - ang;

    QPointF arrowP1 = line.p1() + QPointF(std::sin(line.angle() + PI / 3) * arrowSize,
                                            std::cos(line.angle() + PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(std::sin(line.angle() + PI - PI / 3) * arrowSize,
                                            std::cos(line.angle() + PI - PI / 3) * arrowSize);

*/

    QLineF arrowHead1;
    arrowHead1.setPoints(secondPoint,firstPoint);
    arrowHead1.setLength(100);
    arrowHead1.setAngle(arrowHead1.angle()+20);
    painter->drawLine(arrowHead1);

    QLineF arrowHead2;
    arrowHead2.setPoints(secondPoint,firstPoint);
    arrowHead2.setLength(100);
    arrowHead2.setAngle(arrowHead2.angle()-20);
    painter->drawLine(arrowHead2);
   // painter->drawLine(secondPoint,arrowP2);
   // getAngle(firstPoint, secondPoint);
}

QRectF ArrowMarker::boundingRect() const
{
    //Q_D(const QGraphicsItemGroup);
    //return QRectF(QPoint((firstPoint.x()/2),(firstPoint.y()/2)),QPoint((secondPoint.x()/2),(secondPoint.y()/2)));
    return QRectF(QPoint(firstPoint),QPoint(secondPoint));
}

QPainterPath ArrowMarker::shape() const{
    QPainterPath ret;
    ret.addRect(QRectF(QPoint(firstPoint),QPoint(secondPoint)));
    return ret;
}

double ArrowMarker::getAngle(QPoint pnt1, QPoint pnt2)
{
    double lineLenght = metric(pnt1,pnt2);

    qDebug()<<"arctan "<<qAtan2(pnt2.x(),pnt2.y());
    QLine horizontalLine;
    horizontalLine.setP1(pnt1);
    horizontalLine.setP2(pnt2);
    qDebug()<<"lineLenght "<<lineLenght;
    qDebug()<<"horizontalLine.dy() "<<horizontalLine.dx();
    qDebug()<<"qAtan2 "<<qAcos(horizontalLine.dx()/lineLenght)*180.0/3.14;
    return qAcos(horizontalLine.dy()/lineLenght)*180.0/3.14;
}

int ArrowMarker::metric(QPoint pnt1, QPoint pnt2)
{
    return qSqrt(qPow(pnt1.x() - pnt2.x(),2) + qPow(pnt1.y() - pnt2.y(),2));
}
