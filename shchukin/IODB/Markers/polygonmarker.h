#ifndef POLYGONMARKER_H
#define POLYGONMARKER_H
#include "advancedabstractfigure.h"
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

class PolygonMarker  : public QObject, public AdvancedAbstractFigure
{
public:
    PolygonMarker();
    double getAngle(QPoint pnt1, QPoint pnt2);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QRectF sceneBoundingRect() const;
    QPainterPath shape() const;
};

#endif // POLYGONMARKER_H
