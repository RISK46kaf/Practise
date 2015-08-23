#ifndef MYELLIPSE_H
#define MYELLIPSE_H

#include "shapebase.h"

namespace Figures {

class Ellipse: public ShapeBase
{
    Q_OBJECT
public:
    explicit Ellipse(QObject*  parent = 0);
    explicit Ellipse(QRect coordinates, QObject *parent = 0);
    Ellipse(QRect coordinates,uint color, QObject *parent = 0);

    virtual ~Ellipse();

    QRect getCoordinates() const;
    void setCoordinates(const QRect& coordinates);
    void setCoordinates(const QPoint &topleft, const QPoint &bottomright);
    void setCoordinates(const QPoint &topleft, const QSize &size);
    void setCoordinates(int left, int top, int width, int height);
private:
    QRect m_coordinates;

private:
    void setStrData() final;
};

}
#endif // MYELLIPSE_H
