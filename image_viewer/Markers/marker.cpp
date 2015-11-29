#include "marker.h"

Marker::Marker()
{

}

Marker::~Marker()
{

}

void Marker::drawArrow()
{
    item = new ArrowMarker();
    item->setFirstPnt(centralPnt);
    item->setSecondPnt(secPnt);
}

void Marker::setFirstPoint(QPoint pnt)
{
    centralPnt = pnt;
    secPnt = pnt;
    item->setFirstPnt(centralPnt);
    if(item != NULL)
        item->update();
}

void Marker::setScecondPoint(QPoint pnt)
{
    secPnt = pnt;
    item->setSecondPnt(secPnt);
    if(item != NULL)
        item->update();
}


int Marker::metric(QPoint pnt1, QPoint pnt2)
{
    return qSqrt(qPow(pnt1.x() - pnt2.x(),2) + qPow(pnt1.y() - pnt2.y(),2));

}
