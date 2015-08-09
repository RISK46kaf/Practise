#include "figures.h"

Ellipse::Ellipse()
{
    m_figure_type = FigureType::EllipseFigure;
    setStrData();
}

Ellipse::Ellipse(QRect coordinates):m_coordinates(coordinates)
{
    m_figure_type = FigureType::EllipseFigure;
    setStrData();
}

Ellipse::Ellipse(QRect coordinates, uint color):m_coordinates(coordinates)
{
    m_color = color;
    m_figure_type = FigureType::EllipseFigure;
    setStrData();
}

QRect Ellipse::getCoordinates() const
{
    return m_coordinates;
}

void Ellipse::setCoordinates(const QRect &coordinates)
{
    m_coordinates = coordinates;
    setStrData();
}

void Ellipse::setCoordinates(const QPoint &topleft, const QPoint &bottomright)
{
    m_coordinates = QRect(topleft,bottomright);
    setStrData();
}

void Ellipse::setCoordinates(const QPoint &topleft, const QSize &size)
{
    m_coordinates = QRect(topleft,size);
    setStrData();
}

void Ellipse::setCoordinates(int left, int top, int width, int height)
{
    m_coordinates = QRect(left,top,width,height);
    setStrData();
}

ShapeBase* Ellipse::toRect()
{
    return (ShapeBase*)new Rect(m_coordinates);
}

void Ellipse::setStrData()
{
    m_str_data = "";
    m_str_data.append(m_str_list[m_figure_type]);
    m_str_data.append(";");
    m_str_data.append(QString("ID:%1").arg(m_ID));
    m_str_data.append(";");
    m_str_data.append(serialize(m_coordinates).toBase64());
    m_str_data.append(";");
    m_str_data.append(QString("Color:#%1").arg(QString::number(m_color,16)));
}

