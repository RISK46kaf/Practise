#include "shapebase.h"

ShapeBase::ShapeBase():m_ID(-1),m_evidence_ID(-1),m_color(0xFFFFFFFF),m_str_list({"NoF","Arr","Ell","Pen","Pol","Rec"}),
    m_figure_type(FigureType::NoFigure),m_str_data("")
{
    ;
}

ShapeBase::~ShapeBase()
{
    ;
}

int ShapeBase::getID() const
{
    return m_ID;
}

int ShapeBase::getEvidenceID() const
{
    return m_evidence_ID;
}

uint ShapeBase::getColor() const
{
    return m_color;
}

FigureType ShapeBase::getFigureType() const
{
    return m_figure_type;
}

const QString& ShapeBase::getStrData() const
{
    return m_str_data;
}

void ShapeBase::setID(int ID)
{
    m_ID = ID;
    setStrData();
}

void ShapeBase::setEvidenceID(int ID)
{
    m_evidence_ID = ID;
    setStrData();
}

void ShapeBase::setColor(uint Color)
{
    m_color = Color;
    setStrData();
}

