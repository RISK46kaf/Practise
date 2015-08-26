#include "shapebase.h"

namespace Figures {


ShapeBase::ShapeBase(QObject *parent): QObject(parent),
    m_ID(-1),m_evidence_ID(-1),m_entry_ID(-1),m_diagnosis_ID(-1),m_width(2),m_color(0xFFFFFFFF),m_str_list({"NoF","Arr","Ell","Pol","Rec"}),
    m_figure_type(FigureType::NoFigure),m_str_data("")
{
    ;
}

ShapeBase::~ShapeBase()
{
    ;
}

qint64 ShapeBase::getID() const
{
    return m_ID;
}

qint64 ShapeBase::getEvidenceID() const
{
    return m_evidence_ID;
}

qint64 ShapeBase::getEntryID() const
{
    return m_entry_ID;
}

qint64 ShapeBase::getDiagnosisID() const
{
    return m_diagnosis_ID;
}

int ShapeBase::getWidth() const
{
    return m_width;
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

void ShapeBase::setID(qint64 ID)
{
    m_ID = ID;
    setStrData();
}

void ShapeBase::setEvidenceID(qint64 ID)
{
    m_evidence_ID = ID;
    setStrData();
}

void ShapeBase::setEntryID(qint64 ID)
{
    m_entry_ID = ID;
    setStrData();
}

void ShapeBase::setDiagnosisID(qint64 ID)
{
    m_entry_ID = ID;
    setStrData();
}

void ShapeBase::setWidth(int width)
{
    m_width = width;
}

void ShapeBase::setColor(uint Color)
{
    m_color = Color;
    setStrData();
}

void ShapeBase::clear()
{
    m_ID = -1;
    m_evidence_ID = -1;
    m_entry_ID = -1;
    m_diagnosis_ID = -1;
    m_width = 2;
    m_color = 0xFFFFFFFF;
    m_str_list = QStringList({"NoF","Arr","Ell","Pol","Rec"});
    m_figure_type = FigureType::NoFigure;
    m_str_data = QString();
}

void ShapeBase::setStrData()
{

}


}
