#ifndef FIGURESMANAGER_H
#define FIGURESMANAGER_H

#include <QObject>
#include <QWidget>
#include <QHash>
#include <QPainter>

namespace Figures {

class Rect;
class Polygon;
class Ellipse;
class Arrow;
class ShapeBase;

enum Tool {
    NoTool,
    ArrowTool,
    EllipseTool,
    PolygonTool,
    RectTool/*,
    Wizard*/
};


class FiguresManager : public QObject
{
    Q_OBJECT
public:

    explicit FiguresManager(QObject *parent = 0);

    FiguresManager(const FiguresManager& other);

    virtual ~FiguresManager();

    FiguresManager& operator=(const FiguresManager& other);

    ShapeBase* value(qint64 id) const;

    qint64 addValue(ShapeBase* value);

    void clear();

    void setCurrentParams(qint64 evidenceID, qint64 entryID, qint64 diagnosisID, uint color, Tool tool);

    void drawer(QPainter *aPainter,
                 QPen *aPen, qreal scale) const;

    void musePress(QMouseEvent *anEvent);
    void mouseMove(QMouseEvent *anEvent);

    void magic(QMouseEvent *anEvent);

    bool confirm();
private:
    qint64 m_id;
//    qint64 m_evidence_id;
//    qint64 m_entry_id;
//    qint64 m_diagnosis_id;
    Tool m_tool;
    ShapeBase* m_temp_figure;
    QHash< qint64,ShapeBase* > m_figures;

private:
    void drawArrow(QPainter *painter,
                   QPen *pen,
                   Arrow* arrowObj,
                   qreal scale) const;
    void drawEllipse(QPainter *painter,
                     QPen *pen,
                     Ellipse* ellipseObj,
                     qreal scale) const;
    void drawPolygon(QPainter *painter,
                     QPen *pen,
                     Polygon* polygonObj,
                     qreal scale) const;
    void drawRect(QPainter *painter,
                  QPen *pen,
                  Rect* rectObj,
                  qreal scale) const;
    void drawFigures(QPainter *painter,
                     QPen *pen,
                     qreal scale) const;
};

}
#endif // FIGURESMANAGER_H

