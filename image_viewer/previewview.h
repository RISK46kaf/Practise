#ifndef PREVIEWVIEW_H
#define PREVIEWVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include "rectitem.h"
class PreviewView : public QGraphicsView
{
    Q_OBJECT
public:
    PreviewView();
    ~PreviewView();
    RectItem* rectItem;
    QGraphicsScene* scene;
    QRect rect;
    uint scale;
    void reDraw();
    RectItem *getRectItem();
    QGraphicsPixmapItem pixItem;
signals:

public slots:
    void setR(QRect r);
    void setP(QPointF p);
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
private:
    QRect getViewField(QRect in);
};

#endif // PREVIEWVIEW_H
