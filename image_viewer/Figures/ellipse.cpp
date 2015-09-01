#include "ellipse.h"

namespace Figures {

Ellipse::Ellipse(QObject *parent) : ShapeBase(parent)
{
    m_figure_type = FigureType::EllipseFigure;
    setStrData();
}

Ellipse::Ellipse(QRect coordinates, QObject *parent): ShapeBase(parent),
    m_coordinates(coordinates)
{
    m_figure_type = FigureType::EllipseFigure;
    setStrData();
}

Ellipse::Ellipse(QRect coordinates, uint color, QObject *parent): ShapeBase(parent),
    m_coordinates(coordinates)
{
    m_color = color;
    m_figure_type = FigureType::EllipseFigure;
    setStrData();
}

Ellipse::~Ellipse()
{
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
    m_coordinates =  m_coordinates.normalized();
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

FigureType Ellipse::clearFigure()
{
    ShapeBase::clear();
    m_coordinates = QRect();
    m_figure_type = FigureType::EllipseFigure;
    setStrData();
    return m_figure_type;
}

bool Ellipse::hasDefaultCoordinates()
{
    return m_coordinates == QRect();
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

}
