#ifndef ARROW_H
#define ARROW_H

#include "shapebase.h"
#include <QDebug>

namespace Figures {

class Arrow: public ShapeBase
{
    Q_OBJECT
public:
    explicit Arrow(QObject* parent = 0);
    explicit Arrow(QLineF coordinates, QObject* parent = 0);
    Arrow(QLineF coordinates, uint color, QObject* parent = 0);

    Arrow(const Arrow& other);

    virtual ~Arrow();

    QLineF getCoordinates() const;
    qreal getArrowScale() const;

    void setArrowScale(qreal arrowScale);
    void setCoordinates(const QLineF& coordinates);
    void setCoordinates(const QPointF &pt1, const QPointF &pt2);
    void setCoordinates(qreal x1, qreal y1, qreal x2, qreal y2);
    void setCoordinates(const QLine &line);
    FigureType clearFigure();
private:
    QLineF m_coordinates;
    qreal m_arrow_scale;

private:
    void setStrData() final;
};

}
#endif // ARROW_H
