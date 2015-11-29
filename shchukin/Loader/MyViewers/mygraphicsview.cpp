#include "mygraphicsview.h"
#include "Figures/figuresmanager.h"
#include <QScrollArea>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QMouseEvent>

using namespace MyViewers;
using namespace Figures;

MyGraphicsView::MyGraphicsView(QWidget* parent) :
    QGraphicsView(parent)
{
    setMouseTracking(true);
    _figuresManager->setScroll(horizontalScrollBar(),verticalScrollBar(),viewport()->size());
}

MyGraphicsView::MyGraphicsView(FiguresManager *figuresManager, QWidget *parent) :
    QGraphicsView(parent), _figuresManager(figuresManager)
{
    setMouseTracking(true);
    _figuresManager->setScroll(horizontalScrollBar(),verticalScrollBar(),viewport()->size());
}

void MyGraphicsView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    QGraphicsView::resizeEvent(event);
    emit resized();
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(event->delta() >5)
    {
        emit zoomIn(event->pos());
    }
    if(event->delta() <-5)
    {
        emit zoomOut(event->pos());
    }
}

void MyGraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    _figuresManager->drawer(viewport());
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    _figuresManager->mousePress(this,event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    _figuresManager->mouseMove(this,event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    _figuresManager->mouseRelease();
}


void MyGraphicsView::scrollEvent()
{
    emit scrolled();
}

