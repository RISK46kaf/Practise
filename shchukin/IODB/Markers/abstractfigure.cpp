﻿#include "abstractfigure.h"


AbstractFigure::AbstractFigure()
{
    width = 1;
}

AbstractFigure::AbstractFigure(QPoint f, QPoint s, uint scale, uint w, QRgb c)
{
    firstPoint = f;
    secondPoint = s;
    firstScale = scale;
    color = c;
    width = w;
}

void AbstractFigure::setFirstPnt(QPoint pnt)
{
    this->setScale(1);
    firstPoint = pnt;
    secondPoint = pnt;
    update(this->boundingRect());
    this->prepareGeometryChange();
    //qDebug()<<"!!1"<<secondPoint;
}


void AbstractFigure::setSecondPnt(QPoint pnt)
{
    secondPoint = pnt;
    this->prepareGeometryChange();
    update(this->boundingRect());
    this->prepareGeometryChange();
    //qDebug()<<"!!1"<<secondPoint;

}

void AbstractFigure::scaleChange(int a)
{
    QTransform tr;
    tr.scale(a,a);
    this->prepareGeometryChange();
    //this->setTransform(tr);
    this->setScale(a);
}
