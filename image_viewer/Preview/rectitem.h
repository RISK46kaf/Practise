#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QDebug>

class RectItem : public QGraphicsItem
{

public:
    RectItem(QRectF bRect);
    ~RectItem();
    QRect rect;
    uint scale;
    QRectF br;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setRect(QRect r);
    QPointF centerPos;
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // RECTITEM_H
