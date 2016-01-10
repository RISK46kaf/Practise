#ifndef MYRECT_H
#define MYRECT_H

#include "shapebase.h"
namespace Figures {

class Rect: public ShapeBase
{
    Q_OBJECT
public:
    explicit Rect(QObject *parent = 0);
    explicit Rect(QRect coordinates, QObject *parent = 0);
    Rect(QRect coordinates, uint color);

    virtual ~Rect();

    QRect getCoordinates() const;
    virtual QList<QPoint> coordinatesList() const final;

    void setCoordinates(const QRect& coordinates);
    void setCoordinates(const QPoint &topleft, const QPoint &bottomright);
    void setCoordinates(const QPoint &topleft, const QSize &size);
    void setCoordinates(int left, int top, int width, int height);
    FigureType clearFigure();
    virtual bool hasDefaultCoordinates() final;
private:
    QRect m_coordinates;

private:
    virtual void setStrData() final;
};
}
#endif // MYRECT_H