#ifndef MYSHAPEBASE_H
#define MYSHAPEBASE_H

#include <QtGui>
#include <QObject>

namespace Figures {

enum FigureType
{
    NoFigure,
    ArrowFigure,
    EllipseFigure,
    PolygonFigure,
    RectFigure,
};

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

class ShapeBase: public QObject
{
    Q_OBJECT
public:
    ShapeBase(QObject* parent = 0);
    virtual ~ShapeBase();
    qint64 getID() const;
    qint64 getEvidenceID() const;
    qint64 getEntryID() const;
    qint64 getDiagnosisID() const;
    int getWidth() const;

    uint getColor() const;
    FigureType getFigureType() const;
    const QString& getStrData() const;

    void setID(qint64 ID);
    void setEvidenceID(qint64 ID);
    void setEntryID(qint64 ID);
    void setDiagnosisID(qint64 ID);
    void setWidth(int width);

    void setColor(uint Color);
protected:
    qint64 m_ID;
    qint64 m_evidence_ID;
    qint64 m_entry_ID;
    qint64 m_diagnosis_ID;
    int m_width;

    uint m_color;
    QStringList m_str_list/* = {"NoF","Arr","Ell","Pen","Pol","Rec"}*/;
    FigureType m_figure_type;
    virtual void setStrData();
    QString m_str_data;
};
}
#endif // MYSHAPEBASE

