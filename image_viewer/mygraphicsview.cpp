#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView() :
    QGraphicsView()
{
}

void MyGraphicsView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    QGraphicsView::resizeEvent(event);
    emit resized();
}


void MyGraphicsView::scrollEvent()
{
    emit scrolled();
}

