#ifndef FIGURESMANAGER_H
#define FIGURESMANAGER_H

#include <QObject>
#include <QWidget>
#include <QHash>

#include "DB/defaultnames.h"
#include <QSqlDatabase>

class QSqlDatabase;
class QWidget;
class QPainter;
class QScrollArea;

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

    explicit FiguresManager(QSqlDatabase& dataBase,QObject *parent = 0);

    FiguresManager(const FiguresManager& other);

    virtual ~FiguresManager();

    FiguresManager& operator=(const FiguresManager& other);

    void setScrollArea(QScrollArea* scrollArea);

    ShapeBase* value(qint64 id) const;

    qint64 addValue(ShapeBase* value);

    ShapeBase* takeAt(qint64 id);

    int removeAt(qint64 id);

    void clear();

    void setCurrentParams(qint64 evidenceID, qint64 entryID, qint64 diagnosisID, uint color, Tool tool);

    void drawer(QPainter *aPainter,
                 QPen *aPen, qreal scale) const;

    void musePress(QWidget* widget, QMouseEvent *event, qreal scale);
    void mouseMove(QWidget* widget, QMouseEvent *event, qreal scale);
    void mouseRelease();

//    void magic(QMouseEvent *anEvent);

    bool confirm();

    int connectToDb(QSqlDatabase& d,
                     bool useDefaultParams = false,
                     const QString& host = DB::DefaultDbSettings::HOST,
                     const QString& user = DB::DefaultDbSettings::USER,
                     const QString& pass = DB::DefaultDbSettings::PASS);

    bool isDbConnected() const;

    bool insertData();

    bool selectData();

    bool correctLocalData(qint64 corection);

private:
    qint64 m_id;
    qint64 m_last_mark_id;
    Tool m_tool;
    Tool m_last_tool;
    ShapeBase* m_temp_figure;
    QHash< qint64,ShapeBase* > m_figures;
    QPoint m_prev_cursor;
    bool m_new_selection;
    QScrollArea* m_scroll_area;
    QSqlDatabase m_db;

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
    qint64 getDbLastMarkID();
};

}
#endif // FIGURESMANAGER_H

