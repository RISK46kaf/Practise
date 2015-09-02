#include "view.h"

View::View(QWidget *parent) :
    QWidget(parent)
{
}

void View::setImage(QImage &i)
{
    img = i;
}

void View::paintEvent(QPaintEvent* evt)
{
    QWidget::paintEvent(evt);
    QPainter painter(this);
    if(!img.isNull())
    {
        painter.drawImage(QPoint(0,0),img);
    }
}
