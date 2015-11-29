#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView() :
    QGraphicsView()
{
    scale = 1;
}

void MyGraphicsView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    QGraphicsView::resizeEvent(event);
    emit resized();
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(event->delta() >0)
    {
        emit zoomIn(event->pos());
    }
    if(event->delta() <0)
    {
        emit zoomOut(event->pos());
    }
}


void MyGraphicsView::scrollEvent()
{
    emit scrolled();
}

