#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QDebug>

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphicsScene();

signals:
    void mousePressPos(QPoint pnt);
    void mouseReleasePos(QPoint pnt);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
};

#endif // MYGRAPHICSSCENE_H
