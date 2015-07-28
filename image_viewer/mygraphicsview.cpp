#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView() :
    QGraphicsView()
{
}

void MyGraphicsView::resizeEvent(QResizeEvent *event)
{
    emit resized();
}


void MyGraphicsView::scrollEvent()
{
    emit scrolled();
}

