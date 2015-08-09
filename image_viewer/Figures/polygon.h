#ifndef POLYGON_H
#define POLYGON_H

#include "shapebase.h"

class Polygon: public ShapeBase
{
public:
    Polygon();
    explicit Polygon(QPolygon coordinates);
    Polygon(QPolygon coordinates, uint color);

    QPolygon getCoordinates() const;

    void setCoordinates(const QPolygon& coordinates);
    void setCoordinates(const QVector<QPoint> &coordinates);
    void setCoordinates(const QRect &r, bool closed=false);
private:
    QPolygon m_coordinates;

private:
    void setStrData();
};

#endif // POLYGON_H
