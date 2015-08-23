#include "rect.h"


namespace Figures {

Rect::Rect(QObject *parent) : ShapeBase(parent)
{
    m_figure_type = FigureType::RectFigure;
    setStrData();
}

Rect::Rect(QRect coordinates, QObject *parent): ShapeBase(parent),
    m_coordinates(coordinates)
{
    m_figure_type = FigureType::RectFigure;
    setStrData();
}

Rect::Rect(QRect coordinates, uint color):m_coordinates(coordinates)
{
    m_color = color;
    m_figure_type = FigureType::RectFigure;
    setStrData();
}

Rect::~Rect()
{
}

QRect Rect::getCoordinates() const
{
    return m_coordinates;
}

void Rect::setCoordinates(const QRect &coordinates)
{
    m_coordinates = coordinates;
    setStrData();
}

void Rect::setCoordinates(const QPoint &topleft, const QPoint &bottomright)
{
    m_coordinates = QRect(topleft,bottomright);
    setStrData();
}

void Rect::setCoordinates(const QPoint &topleft, const QSize &size)
{
    m_coordinates = QRect(topleft,size);
    setStrData();
}

void Rect::setCoordinates(int left, int top, int width, int height)
{
    m_coordinates = QRect(left,top,width,height);
    setStrData();
}

void Rect::setStrData()
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
