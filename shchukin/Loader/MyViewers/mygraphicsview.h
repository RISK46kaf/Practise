#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>

namespace Figures {

class FiguresManager;

}

class QResizeEvent;
class QScrollArea;
class QPaintEvent;

namespace MyViewers {

class MyGraphicsView :public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget* parent = 0);
    explicit MyGraphicsView(Figures::FiguresManager* figuresManager,QWidget* parent = 0);
private:
    Figures::FiguresManager* _figuresManager;
    uint* _scale;
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
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

}
#endif // MYGRAPHICSVIEW_H
