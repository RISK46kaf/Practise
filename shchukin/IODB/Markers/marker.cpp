#include "marker.h"

Marker::Marker()
{
    currentScale = 1;
    item = NULL;
    advancedItem = NULL;
}

Marker::~Marker()
{

}

void Marker::drawArrow()
{
    item = new ArrowMarker();
    item->setFirstPnt(QPoint(0,0));
    item->setSecondPnt(QPoint(0,0));
    name = "Arrow";
}

void Marker::drawEllipse()
{
    item = new EllipseMarker();
    item->setFirstPnt(QPoint(0,0));
    item->setSecondPnt(QPoint(0,0));
    name = "Ellipse";
}


void Marker::drawRect()
{
    item = new RectMarker();
    item->setFirstPnt(QPoint(0,0));
    item->setSecondPnt(QPoint(0,0));
    name = "Rect";
}

void Marker::drawPolygon()

{
    advancedItem = new PolygonMarker();

    name = "Polygon";
}

void Marker::setFirstPoint(QPoint pnt)
{
    emit(makeUpdate());

    qDebug()<<"setFirstPoint currentScale "<<currentScale;
    setFirstScale(currentScale);
    centralPnt = pnt;
    secPnt = pnt;
    item->setFirstPnt(centralPnt);
    if(item != NULL)
        item->update();
}

void Marker::setScecondPoint(QPoint pnt)
{
    emit(makeUpdate());

    secPnt = pnt;
    item->setSecondPnt(secPnt);
    if(item != NULL)
        item->update();
}



void Marker::setFirstScale(uint s)
{
    firstScale = s;
}

void Marker::setScale(uint s)
{
    if(item)
    {
        if(item->firstPoint.x() && item->firstPoint.y())
        {
            currentScale = s;
            QTransform tr;
            double a = firstScale/currentScale;
            qDebug()<<"firstScale "<<firstScale;
            qDebug()<<"a "<<a;
            tr.scale(a,a);
            //item->setTransform(tr);
            //item->prepareGeometryChange();
            //item->scaleChanged();
            item->setScale(a);

            //qDebug()<<"rect "<<item->boundingRect();
            //item->setScale(currentScale/firstScale);
        }
    }
    if(advancedItem)
    {
        currentScale = s;
        QTransform tr;
        double a = firstScale/currentScale;
        qDebug()<<"firstScale "<<firstScale;
        qDebug()<<"a "<<a;
        tr.scale(a,a);
        //item->setTransform(tr);
        //item->prepareGeometryChange();
        //item->scaleChanged();
        advancedItem->setScale(a);

        //qDebug()<<"rect "<<advancedItem->boundingRect();
        //item->setScale(currentScale/firstScale);
    }
}

void Marker::setCurrentScale(uint s)
{
    currentScale = s;
}

void Marker::addPoint(QPoint pnt)
{
    advancedItem->addPoint(pnt);
}

void Marker::setWidth(uint w)
{
    if(item)
        item->width = w;
    if(advancedItem)
        advancedItem->width = w;

}

void Marker::setColor(QRgb c)
{
    if(item)
        item->color = c;
    if(advancedItem)
        advancedItem->color = c;

}
