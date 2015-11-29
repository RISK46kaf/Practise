#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H
#include <QPoint>
#include <QObject>
#include <QGraphicsItem>


class AbstractFigure : public QObject, public QGraphicsItem
{
public:
    AbstractFigure();
    QPoint firstPoint;
    QPoint secondPoint;
    void setFirstPnt(QPoint pnt);
    void setSecondPnt(QPoint pnt);
};

#endif // ABSTRACTFIGURE_H
