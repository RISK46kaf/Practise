#ifndef MARKER_H
#define MARKER_H
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <Markers/abstractfigure.h>
#include <Markers/arrowmarker.h>
#include "ellipsemarker.h"
#include "rectmarker.h"
#include "advancedabstractfigure.h"
#include "polygonmarker.h"
#include <QTextDocument>


class Marker : public QObject
{
    Q_OBJECT
public:
    Marker();
    ~Marker();
    void drawArrow();
    void drawEllipse();

    QPoint centralPnt;
    QPoint secPnt;
    AbstractFigure* item;
    AdvancedAbstractFigure* advancedItem;

    QString name;
    QString text;
    double firstScale;
    double currentScale;
    void setScale(uint s);
    void setFirstScale(uint s);
    void setWidth(uint w);
    void setColor(QRgb c);
    void drawRect();
    void drawPolygon();
    int id;
public slots:
    void setFirstPoint(QPoint pnt);
    void setScecondPoint(QPoint pnt);
    void setCurrentScale(uint s);
    void addPoint(QPoint pnt);
private:
    int metric(QPoint pnt1, QPoint pnt2);
signals:
    void makeUpdate();

};

#endif // MARKER_H
