#ifndef MYPOLYGON_H
#define MYPOLYGON_H

#include "shapebase.h"

namespace Figures {

class Polygon: public ShapeBase
{
    Q_OBJECT
public:
    explicit Polygon(QObject *parent = 0);
    explicit Polygon(QPolygon coordinates, QObject *parent = 0);
    Polygon(QPolygon coordinates, uint color, QObject *parent = 0);

    virtual ~Polygon();

    QPolygon getCoordinates() const;

    void setCoordinates(const QPolygon& coordinates);
    void setCoordinates(const QVector<QPoint> &coordinates);
    void setCoordinates(const QRect &r, bool closed=false);
    void appendPoint(const QPoint& newPoint);
    FigureType clearFigure();
private:
    QPolygon m_coordinates;

private:
    void setStrData() final;
};
}
#endif // MYPOLYGON_H
