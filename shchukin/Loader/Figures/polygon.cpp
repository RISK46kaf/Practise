#include "polygon.h"
#include <QDebug>
namespace Figures {


Polygon::Polygon(QObject *parent) : ShapeBase(parent)
{
    m_figure_type = FigureType::PolygonFigure;
    setStrData();
}

Polygon::Polygon(QPolygon coordinates, QObject *parent): ShapeBase(parent),
    m_coordinates(coordinates)
{
    m_figure_type = FigureType::PolygonFigure;
    setStrData();
}

Polygon::Polygon(QPolygon coordinates, uint color, QObject *parent): ShapeBase(parent),
    m_coordinates(coordinates)
{
    m_color = color;
    m_figure_type = FigureType::PolygonFigure;
}

Polygon::~Polygon()
{
}


QPolygon Polygon::getCoordinates() const
{
    return m_coordinates;
}

QList<QPoint> Polygon::coordinatesList() const
{
    return m_coordinates.toList();
}

void Polygon::setCoordinates(const QPolygon &coordinates)
{
    m_coordinates = coordinates;
    setStrData();
}

void Polygon::setCoordinates(const QVector<QPoint> &coordinates)
{
    m_coordinates = QPolygon(coordinates);
    setStrData();
}

void Polygon::setCoordinates(const QRect &r, bool closed)
{
    m_coordinates = QPolygon(r,closed);
    setStrData();
}

void Polygon::appendPoint(const QPoint &newPoint)
{
    m_coordinates << newPoint;
    setStrData();
}

FigureType Polygon::clearFigure()
{
    qDebug() << "clear" << m_figure_type;
    ShapeBase::clear();
    m_coordinates = QPolygon();
    m_figure_type = FigureType::PolygonFigure;
    setStrData();
    return m_figure_type;
}

bool Polygon::hasDefaultCoordinates()
{
    return m_coordinates == QPolygon();
}

void Polygon::setStrData()
{
    m_str_data = "";
    m_str_data.append(m_str_list[m_figure_type]);
    m_str_data.append(";");
    m_str_data.append(QString("ID:%1").arg(m_ID));
    m_str_data.append(";");
    m_str_data.append(serialize(m_evidence_key).toBase64());
    m_str_data.append(";");
    m_str_data.append(serialize(m_coordinates).toBase64());
    m_str_data.append(";");
    m_str_data.append(QString("Color:#%1").arg(QString::number(m_color,16)));
}

}