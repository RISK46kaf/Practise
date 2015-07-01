#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <type_traits>
#include <set>

enum Figure
{
    NoFigure,
    ArrowFigure,
    EllipseFigure,
    PolygonFigure,
    PenFigure,
    RectFigure,
};

class ShapeInterface
{
protected:
    int _label_ID;
    uint _color;
public:
    virtual int getLabelID() = 0;
    virtual void setLabelID(int ID) = 0;
    virtual uint getColor() = 0;
    virtual void setColor(uint Color) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Shape: public ShapeInterface
{
    T _coordinates;
public:
    int getLabelID()
    {
        return _label_ID;
    }
    uint getColor()
    {
        return _color;
    }

    T getCoordinates()
    {
        return _coordinates;
    }


    void setLabelID(int ID)
    {
        _label_ID = ID;
    }

    void setColor(uint Color)
    {
        _color = Color;
    }

    void setCoordinates(const T& coordinates)
    {
        _coordinates = coordinates;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Shape<QLineF> Arrow;
typedef Shape<QPolygon> Polygon;
typedef Shape<std::set<QPoint> > Pen;

class Ellipse: public Shape<QRect>
{
public:
    Ellipse() {}
    virtual ~Ellipse() {}
};

class Rect : public Shape<QRect>
{
public:
    Rect() {}
    virtual ~Rect() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MakedFigureInterface
{
public:
    virtual Figure getFigure() = 0;
//    virtual auto toMakedFigure() = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class F>
class MakedFigure: public MakedFigureInterface, F
{
    Figure _figure_type;
public:
    MakedFigure()
    {
        if(std::is_same<F,Arrow>::value)
        {
            _figure_type = Figure::ArrowFigure;
        }
        else if(std::is_same<F,Ellipse>::value)
        {
            _figure_type = Figure::EllipseFigure;
        }
        else if(std::is_same<F,Pen>::value)
        {
            _figure_type = Figure::PenFigure;
        }
        else if(std::is_same<F,Polygon>::value)
        {
            _figure_type = Figure::PolygonFigure;
        }
        else if(std::is_same<F,Rect>::value)
        {
            _figure_type = Figure::RectFigure;
        }
        else
        {
            _figure_type = Figure::NoFigure;
        }
    }

//    auto toMakedFigure()
//    {
//        return reinterpret_cast<MakedFigure<F> > (&this);
//    }

    Figure getFigure()
    {
        return _figure_type;
    }
};
#endif // SHAPE_H
