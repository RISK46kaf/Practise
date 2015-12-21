#ifndef RECTMARKER_H
#define RECTMARKER_H
#include "abstractfigure.h"
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

class RectMarker  : public QObject, public AbstractFigure
{
public:
    RectMarker();
    double getAngle(QPoint pnt1, QPoint pnt2);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QRectF sceneBoundingRect() const;
    QPainterPath shape() const;
};

#endif // RECTMARKER_H
