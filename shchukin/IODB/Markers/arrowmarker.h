#ifndef ARROWMARKER_Hn
#define ARROWMARKER_H
#include "abstractfigure.h"
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

class ArrowMarker  : public QObject, public AbstractFigure
{
public:
    ArrowMarker();
    void test();
    double getAngle(QPoint pnt1, QPoint pnt2);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QRectF sceneBoundingRect() const;
    QPainterPath shape() const;
private:
    int metric(QPoint pnt1, QPoint pnt2);
};

#endif // ARROWMARKER_H
