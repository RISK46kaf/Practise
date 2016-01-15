#ifndef ADVANCEDABSTRACTFIGURE_H
#define ADVANCEDABSTRACTFIGURE_H
#include <QPoint>
#include <QObject>
#include <QGraphicsItem>
#include <QDebug>

class AdvancedAbstractFigure : public QGraphicsItem
{
public:
    AdvancedAbstractFigure();
    AdvancedAbstractFigure(uint scale, uint w, QRgb c);
    QVector<QPoint> points;
    uint firstScale;
    uint currentScale;
    QRectF imageRect;
    uint width;
    QRgb color;
    QPolygon poly;
    QRect bRect;
    void scaleChange(int a);
    void addPoint(QPoint pnt);
    int maxTop;
    int maxBottom;
    int maxLeft;
    int maxRight;
};

#endif // ADVANCEDABSTRACTFIGURE_H
