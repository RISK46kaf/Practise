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
#include <Preview/previewview.h>
#include <QListWidget>
#include "Markers/marker.h"
#include "mygraphicsscene.h"


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


    void timeout();

    void setViewPos(QPointF pnt);

    void on_imageListWidget_currentRowChanged(int currentRow);

    void on_actionLoad_Images_2_triggered();

    void on_arrowButton_clicked();

signals:
    void topLeftPointEvent(QPointF);
    void viewRect(QRect r);
private:
    Ui::Viewer *ui;
    Cutter cutter;
    MyGraphicsView* view;
    MyGraphicsView* cmpView;
    PreviewView* preview;
    PreviewView* cmpPreview;
    MyGraphicsScene* scene;
    QGraphicsScene* cmpScene;
    QGraphicsScene* previewScene;
    QGraphicsScene* cmpPreviewScene;
    TileMap* map;
    TileMap* cmpMap;
    QGraphicsPixmapItem *centralItem;
    QStringList paths;
    uint oldValueHorizontal;
    uint oldValueVertical;
    QRect old_view_field;
    uint scale;
    uint cmpScale;
    QSize map_size;
    QRect getViewField();
    QPoint getCentralPoint();
    QStringList imageList;
    QVector<QListWidgetItem*> items;
    QVector<Marker*> markers;
    QTimer* t;

    void setXML(QString path);
    void setPreview(QString path);
    void setMousePos(QPoint pnt);
    bool l;
public slots:
    void markerScaleChange(uint sc);
};


#endif // VIEWER_H
