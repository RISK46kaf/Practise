#include "abstractfigure.h"

AbstractFigure::AbstractFigure()
{

}

void AbstractFigure::setFirstPnt(QPoint pnt)
{
    firstPoint = pnt;
    secondPoint = pnt;
    update(this->boundingRect());
}

void AbstractFigure::setSecondPnt(QPoint pnt)
{
    secondPoint = pnt;
    update(this->boundingRect());
}
