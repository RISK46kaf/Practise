#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <type_traits>
#include <set>
#include <QDebug>

enum FigureType
{
    NoFigure,
    ArrowFigure,
    EllipseFigure,
    PenFigure,
    PolygonFigure,
    RectFigure,
};

class Rect;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
QByteArray serialize(const T& x)
{
    QByteArray ba;
    QDataStream s(&ba, QIODevice::WriteOnly);
    s << x;
    return ba;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
T deserialize(QByteArray& ba)
{
    QDataStream s(&ba, QIODevice::ReadOnly);
    T res; s >> res;
    return res;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ShapeBase
{
protected:
    int _evidence_ID;
    uint _color;
    QStringList _str_list = {"NoF","Arr","Ell","Pen","Pol","Rec"};
    FigureType _figure_type;
    virtual void setStrData(FigureType figureType) = 0;
    QString _str_data;
public:
    int getEvidenceID()
    {
        return _evidence_ID;
    }
    uint getColor()
    {
        return _color;
    }

    void setEvidenceID(int ID)
    {
        _evidence_ID = ID;
    }

    void setColor(uint Color)
    {
        _color = Color;
    }

    FigureType getFigureType()
    {
        return _figure_type;
    }
    QString& getStrData()
    {
        return _str_data;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Ellipse: public ShapeBase
{
    QRect _coordinates;
    void setStrData(FigureType figureType)
    {
        _str_data = "";
        _str_data.append((QByteArray().append(_str_list[figureType])).toBase64());
        _str_data.append(";");
        _str_data.append(serialize(_coordinates).toBase64());
        _str_data.append(";");
//        _str_data.append(QByteArray().append(QString("Color:%1").arg(_color)).toBase64());
    }
public:
    Ellipse()
    {
        _figure_type = FigureType::EllipseFigure;
        setStrData(_figure_type);
    }
    explicit Ellipse(QRect coordinates):_coordinates(coordinates)
    {
        _figure_type = FigureType::EllipseFigure;
        setStrData(_figure_type);
    }
    Ellipse(QRect coordinates,uint color):_coordinates(coordinates)
    {
        _color = color;
        _figure_type = FigureType::EllipseFigure;
        setStrData(_figure_type);
    }

    QRect getCoordinates()
    {
        return _coordinates;
    }

    void setCoordinates(const QRect& coordinates)
    {
        _coordinates = coordinates;
        setStrData(_figure_type);
    }

    Rect toRect();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Rect: public ShapeBase
{
    QRect _coordinates;
    void setStrData(FigureType figureType)
    {
        _str_data = "";
        _str_data.append((QByteArray().append(_str_list[figureType])).toBase64());
        _str_data.append(";");
        _str_data.append(serialize(_coordinates).toBase64());
        _str_data.append(";");
        _str_data.append(QByteArray().append(QString("Color:%1").arg(_color)).toBase64());
    }
public:
    Rect()
    {
        _figure_type = FigureType::RectFigure;
        setStrData(_figure_type);
    }

    explicit Rect(QRect coordinates):_coordinates(coordinates)
    {
        _figure_type = FigureType::RectFigure;
        setStrData(_figure_type);
    }

    Rect(QRect coordinates, uint color):_coordinates(coordinates)
    {
        _color = color;
        _figure_type = FigureType::RectFigure;
        setStrData(_figure_type);
    }

    QRect getCoordinates()
    {
        return _coordinates;
    }

    void setCoordinates(const QRect& coordinates)
    {
        _coordinates = coordinates;
        setStrData(_figure_type);
    }
    Ellipse toEllipse();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Shape: public ShapeBase
{
    T _coordinates;
    void setStrData(FigureType figureType)
    {
        _str_data = "";
        _str_data.append((QByteArray().append(_str_list[figureType])).toBase64());
        _str_data.append(";");
        _str_data.append(serialize(_coordinates).toBase64());
        _str_data.append(";");
        _str_data.append(QByteArray().append(QString("Color:%1").arg(_color)).toBase64());
    }
    inline void setter()
    {
        if(std::is_same<T,QLineF>::value)
        {
            _figure_type = FigureType::ArrowFigure;
            setStrData(_figure_type);
        }
        else if(std::is_same<T,std::set<QPoint> >::value)
        {
            _figure_type = FigureType::PenFigure;
            setStrData(_figure_type);
        }
        else if(std::is_same<T,QPolygon>::value)
        {
            _figure_type = FigureType::PolygonFigure;
            setStrData(_figure_type);
        }
        else
        {
            _figure_type = FigureType::NoFigure;
            setStrData(_figure_type);
        }
    }

public:
    Shape()
    {
        setter();
    }

    explicit Shape(T coordinates):_coordinates(coordinates)
    {
        setter();
    }

    Shape(T coordinates, uint color):_coordinates(coordinates)
    {
        _color = color;
        setter();
    }

    T getCoordinates()
    {
        return _coordinates;
    }

    void setCoordinates(const T& coordinates)
    {
        _coordinates = coordinates;
        setStrData(_figure_type);
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Shape<QLineF> Arrow;
typedef Shape<QPolygon> Polygon;



#endif // SHAPE_H
