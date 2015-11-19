#ifndef FIGURESMANAGER_H
#define FIGURESMANAGER_H

#include <QObject>
#include <QWidget>
#include <QHash>

#include <QSqlDatabase>
#include "Figures/shapebase.h"

class QSqlDatabase;
class QWidget;
class QPainter;
class QScrollBar;


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

//enum FigureType
//{
//    NoFigure,
//    ArrowFigure,
//    EllipseFigure,
//    PolygonFigure,
//    RectFigure,
//};


class FiguresManager : public QObject
{
    Q_OBJECT
public:

    explicit FiguresManager(QObject *parent = 0);

//    explicit FiguresManager(QSqlDatabase& dataBase,QObject *parent = 0);

    FiguresManager(const FiguresManager& other);

    virtual ~FiguresManager();

    FiguresManager& operator=(const FiguresManager& other);

    void setScroll(QScrollBar* horizontal,QScrollBar* vertical,const QSize& size);
    void setScalePointer(uint* scale);

    ShapeBase* value(qint64 id) const;

    qint64 addValue(ShapeBase* value);

    ShapeBase* takeAt(qint64 id);

    bool removeAt(qint64 id);

    void setEvidenceKey(const QString &key);

    QString stringById(qint64 id);

    void clear();

    void setTool(Tool tool);
    void setCurrentColor(uint* currentColor);
    void setCurrentParams(qint64 evidenceID, qint64 entryID, qint64 diagnosisID, uint color, Tool tool);

    void drawer(QWidget *widget);

    void mousePress(QWidget* widget, QMouseEvent *event);
    void mouseMove(QWidget* widget, QMouseEvent *event);
    void mouseRelease();

//    void magic(QMouseEvent *anEvent);

    qint64 confirm();
    void calcDx(int newVal);
    void calcDy(int newVal);

private:
    qint64 m_id;
    qint64 m_last_mark_id;
    Tool m_tool;
    Tool m_last_tool;
    ShapeBase* m_temp_figure;
    QHash< qint64,ShapeBase* > m_figures;
    QHash< qint64,QString > m_data;
    QPoint m_prev_cursor;
    bool m_new_selection;
    QSize m_viewport_size;
    QScrollBar* m_vertical_scroll;
    QScrollBar* m_horizontal_scroll;
    QSqlDatabase m_db;
    uint* _scale;
    uint* _curr_color;
    int _dx;
    int _dy;
    uint _x;
    uint _y;
    QString _ev_key;

private:
    void drawArrow(QPainter *painter,
                   QPen *pen,
                   Arrow* arrowObj);
    void drawEllipse(QPainter *painter,
                     QPen *pen,
                     Ellipse* ellipseObj) ;
    void drawPolygon(QPainter *painter,
                     QPen *pen,
                     Polygon* polygonObj) ;
    void drawRect(QPainter *painter,
                  QPen *pen,
                  Rect* rectObj) ;
    void drawFigures(QWidget *widget);
    qint64 getDbLastMarkID();
};

}
#endif // FIGURESMANAGER_H

