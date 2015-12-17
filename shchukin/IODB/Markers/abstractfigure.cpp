#include "abstractfigure.h"

AbstractFigure::AbstractFigure()
{

}

void AbstractFigure::setFirstPnt(QPoint pnt)
{
    firstPoint = pnt;
    secondPoint = pnt;
    update(this->boundingRect());
    this->prepareGeometryChange();
}

void AbstractFigure::setSecondPnt(QPoint pnt)
{
    secondPoint = pnt;
    this->prepareGeometryChange();
    update(this->boundingRect());
}

void AbstractFigure::scaleChanged()
{
    this->prepareGeometryChange();
}
