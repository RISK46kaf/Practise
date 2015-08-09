#ifndef SHAPEBASE
#define SHAPEBASE

#include <QtGui>

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
public:
    ShapeBase();
    virtual ~ShapeBase();
    int getID() const;
    int getEvidenceID() const;
    uint getColor() const;
    FigureType getFigureType() const;
    const QString& getStrData() const;

    void setID(int ID);
    void setEvidenceID(int ID);
    void setColor(uint Color);
protected:
    int m_ID;
    int m_evidence_ID;
    uint m_color;
    QStringList m_str_list/* = {"NoF","Arr","Ell","Pen","Pol","Rec"}*/;
    FigureType m_figure_type;
    virtual void setStrData() = 0;
    QString m_str_data;
};
#endif // SHAPEBASE

