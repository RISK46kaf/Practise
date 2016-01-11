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
    int factor;
    QRectF br;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setRect(QRect r);
    QPointF centerPos;
    void setFactor(int f);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // RECTITEM_H
