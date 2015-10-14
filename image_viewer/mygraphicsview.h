#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QResizeEvent>
#include <QObject>

class MyGraphicsView :public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView();

signals:
    void resized();
    void changed();
    void scrolled();
    void zoomIn(QPoint pnt);
    void zoomOut(QPoint pnt);
public slots:
    void scrollEvent();
protected:
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent* event);

};

#endif // MYGRAPHICSVIEW_H
