#include "abstractfigure.h"

AbstractFigure::AbstractFigure()
{

}

void AbstractFigure::setFirstPnt(QPoint pnt)
{
    firstPoint = pnt;
}

void AbstractFigure::setSecondPnt(QPoint pnt)
{
    secondPoint = pnt;
}
