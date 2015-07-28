#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include "cutter.h"
#include "tilemap.h"
#include "mygraphicsview.h"
#include <QFileDialog>n
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QScrollBar>

namespace Ui {
class Viewer;
}

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();

private slots:
    void on_actionPrepare_Image_triggered();

    void on_actionLoad_Images_triggered();

    void viewResized();

    void viewChanged();
signals:
    void centralPointEvent(QPointF);
private:
    Ui::Viewer *ui;
    Cutter cutter;
    MyGraphicsView* view;
    QGraphicsScene* scene;
    vector<QGraphicsPixmapItem*> items;
    QRect r;
    TileMap* map;
    QGraphicsPixmapItem *centralItem;

    void drawTiles(QStringList paths, QSize size);
};

#endif // VIEWER_H
