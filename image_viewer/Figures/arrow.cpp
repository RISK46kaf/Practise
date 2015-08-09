#include "shapebase.h"
#include "arrow.h"

Arrow::Arrow()
{
    m_figure_type = FigureType::ArrowFigure;
    setStrData();
}

Arrow::Arrow(QLineF coordinates):m_coordinates(coordinates)
{
    m_figure_type = FigureType::ArrowFigure;
    setStrData();
}

Arrow::Arrow(QLineF coordinates, uint color):m_coordinates(coordinates)
{
    m_color = color;
    m_figure_type = FigureType::ArrowFigure;
    setStrData();
}

QLineF Arrow::getCoordinates() const
{
    return m_coordinates;
}

void Arrow::setCoordinates(const QLineF &coordinates)
{
    m_coordinates = coordinates;
    setStrData();
}

void Arrow::setCoordinates(const QPointF &pt1, const QPointF &pt2)
{
    m_coordinates = QLineF(pt1,pt2);
    setStrData();
}

void Arrow::setCoordinates(qreal x1, qreal y1, qreal x2, qreal y2)
{
    m_coordinates = QLineF(x1,y1,x2,y2);
    setStrData();
}

void Arrow::setCoordinates(const QLine &line)
{
    m_coordinates = QLineF(line);
    setStrData();
}

void Arrow::setStrData()
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
