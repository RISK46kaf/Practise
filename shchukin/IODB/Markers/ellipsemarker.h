#ifndef ELLIPSEMARKER_H
#define ELLIPSEMARKER_H
#include "abstractfigure.h"
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

class EllipseMarker  : public QObject, public AbstractFigure
{
public:
    EllipseMarker();
    double getAngle(QPoint pnt1, QPoint pnt2);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QRectF sceneBoundingRect() const;
    QPainterPath shape() const;
};

#endif // ELLIPSEMARKER_H
