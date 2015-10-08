#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsRectItem>
#include <QPainter>

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

};

#endif // RECTITEM_H
