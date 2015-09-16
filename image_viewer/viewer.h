#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include "cutter.h"
#include "tilemap.h"
#include "mygraphicsview.h"
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QScrollBar>
#include <QXmlStreamReader>

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

    void scrolledVertical(int value);

    void scrolledHorizontal(int value);


    void on_zoomOutButton_clicked();
    void zoomOut(QPoint);
    void zoomIn(QPoint);

    void timeout();

signals:
    void centralPointEvent(QPointF);
private:
    Ui::Viewer *ui;
    Cutter cutter;
    MyGraphicsView* view;
    QGraphicsScene* scene;
    TileMap* map;
    QGraphicsPixmapItem *centralItem;
    QStringList paths;
    uint oldValueHorizontal;
    uint oldValueVertical;
    QRect old_view_field;
    uint scale;
    QVector<QSize> imgSizes;
    QVector<QSize> tileAmount;
    QSize map_size;
    QRect getViewField();
    QPoint getCentralPoint();
    QTimer* t;
    void setMousePos(QPoint pnt);
    bool l;

};


#endif // VIEWER_H
