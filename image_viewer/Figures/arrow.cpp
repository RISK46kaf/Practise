#include "arrow.h"

namespace Figures {

Arrow::Arrow(QObject *parent) : ShapeBase(parent), m_arrow_scale(20)
{
    m_figure_type = FigureType::ArrowFigure;
    setStrData();
}

Arrow::Arrow(QLineF coordinates, QObject *parent): ShapeBase(parent),
    m_coordinates(coordinates), m_arrow_scale(20)
{
    m_figure_type = FigureType::ArrowFigure;
    setStrData();
}

Arrow::Arrow(QLineF coordinates, uint color, QObject *parent): ShapeBase(parent),
    m_coordinates(coordinates), m_arrow_scale(20)
{
    m_color = color;
    m_figure_type = FigureType::ArrowFigure;
    setStrData();
}

Arrow::Arrow(const Arrow &other) : ShapeBase(0)
{
//    m_ID(-1),m_evidence_ID(-1),m_color(0xFFFFFFFF),m_str_list({"NoF","Arr","Ell","Pol","Rec"}),
//    m_figure_type(FigureType::NoFigure),m_str_data("")
    m_ID = other.m_ID;
    m_evidence_ID = other.m_evidence_ID;
    m_color = other.m_color;
    m_str_data = other.m_str_data;
    m_figure_type = other.m_figure_type;
    m_coordinates = other.m_coordinates;
    m_arrow_scale = other.m_arrow_scale;
    setStrData();
}

Arrow::~Arrow()
{
}

qreal Arrow::getArrowScale() const
{
    return m_arrow_scale;
}

QLineF Arrow::getCoordinates() const
{
    return m_coordinates;
}

void Arrow::setArrowScale(qreal arrowScale)
{
    m_arrow_scale = arrowScale;
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

FigureType Arrow::clearFigure()
{
    ShapeBase::clear();
    m_figure_type = FigureType::ArrowFigure;
    m_coordinates = QLineF();
    m_arrow_scale = 20;
    setStrData();
    return m_figure_type;
}

bool Arrow::hasDefaultCoordinates()
{
    return m_coordinates == QLineF();
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

}
