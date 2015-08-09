#ifndef RECT_H
#define RECT_H
#include "ellipse.h"


class ShapeBase;
class Ellipse;

class Rect: public ShapeBase
{
public:
    Rect();
    explicit Rect(QRect coordinates);
    Rect(QRect coordinates, uint color);

    QRect getCoordinates() const;

    void setCoordinates(const QRect& coordinates);
    void setCoordinates(const QPoint &topleft, const QPoint &bottomright);
    void setCoordinates(const QPoint &topleft, const QSize &size);
    void setCoordinates(int left, int top, int width, int height);
    //Ellipse toEllipse();
private:
    QRect m_coordinates;

private:
    void setStrData();
};

#endif // RECT_H
