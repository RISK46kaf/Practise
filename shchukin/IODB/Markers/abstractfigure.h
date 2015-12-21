#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H
#include <QPoint>
#include <QObject>
#include <QGraphicsItem>
#include <QDebug>

class AbstractFigure : public QObject, public QGraphicsItem
{
public:
    AbstractFigure();
    QPoint firstPoint;
    QPoint secondPoint;
    void setFirstPnt(QPoint pnt);
    void setSecondPnt(QPoint pnt);
    uint firstScale;
    uint currentScale;
    QRectF imageRect;
    uint width;
    QRgb color;
    void scaleChange(int a);
};

#endif // ABSTRACTFIGURE_H
