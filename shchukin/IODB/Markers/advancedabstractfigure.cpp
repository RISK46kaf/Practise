#include "advancedabstractfigure.h"

AdvancedAbstractFigure::AdvancedAbstractFigure()
{
    width = 1;
    maxTop = INT32_MAX;
    maxBottom = 0;
    maxLeft = INT32_MAX;
    maxRight = 0;
}

AdvancedAbstractFigure::AdvancedAbstractFigure(uint scale, uint w, QRgb c)
{
    firstScale = scale;
    width = w;
    color = c;
}


void AdvancedAbstractFigure::scaleChange(int a)
{
    QTransform tr;
    tr.scale(a,a);
    this->prepareGeometryChange();
    //this->setTransform(tr);
    this->setScale(a);
}

void AdvancedAbstractFigure::addPoint(QPoint pnt)
{
    this->prepareGeometryChange();
    points.push_back(pnt);
    poly.push_back(pnt);


    if(maxTop > pnt.y())
    {
        maxTop = pnt.y();
        qDebug()<<"maxTop "<<maxTop;
        bRect.setTop(maxTop);
    }
    if(maxBottom < pnt.y())
    {
        maxBottom = pnt.y();
        bRect.setBottom(maxBottom);
    }
    if(maxLeft > pnt.x())
    {
        maxLeft = pnt.x();
        bRect.setLeft(maxLeft);
    }
    if(maxRight < pnt.x())
    {
        maxRight = pnt.x();
        bRect.setRight(maxRight);
    }

    this->prepareGeometryChange();
    qDebug()<<"bRect "<<bRect;
    qDebug()<<"poly.boundingRect()" <<poly.boundingRect();
}
