#include "shape.h"

Rect Ellipse::toRect()
{
    return Rect(_coordinates);
}

Ellipse Rect::toEllipse()
{
    return Ellipse(_coordinates);
}
