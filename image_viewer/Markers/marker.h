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


class Marker : public QObject
{
    Q_OBJECT
public:
    Marker();
    ~Marker();
    void drawArrow();
    QPoint centralPnt;
    QPoint secPnt;
    AbstractFigure* item;
    QTransform tr;
public slots:
    void setFirstPoint(QPoint pnt);
    void setScecondPoint(QPoint pnt);
private:
    int metric(QPoint pnt1, QPoint pnt2);

};

#endif // MARKER_H
