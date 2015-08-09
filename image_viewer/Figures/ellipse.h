#ifndef ELLIPSE_H
#define ELLIPSE_H

class ShapeBase;
class Rect;

class Ellipse: public ShapeBase
{
public:
    Ellipse();
    explicit Ellipse(QRect coordinates);
    Ellipse(QRect coordinates,uint color);
    QRect getCoordinates() const;
    void setCoordinates(const QRect& coordinates);
    void setCoordinates(const QPoint &topleft, const QPoint &bottomright);
    void setCoordinates(const QPoint &topleft, const QSize &size);
    void setCoordinates(int left, int top, int width, int height);
    Rect toRect();
private:
    QRect m_coordinates;

private:
    void setStrData();
};

#endif // ELLIPSE_H
