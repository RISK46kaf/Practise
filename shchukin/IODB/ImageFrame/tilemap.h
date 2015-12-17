#ifndef TILEMAP_H
#define TILEMAP_H
#include <QImage>
#include <QStringList>
#include <QObject>
#include <QDebug>
#include "tile.h"
#include <QQueue>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScrollBar>
#include <QStack>
#include <QVector>
#include <QString>
#include <QtMath>
#include "Preview/previewview.h"
#ifdef Q_OS_WIN32
#include <windows.h>
#endif
#include <QDir>

class TileMap: public QObject
{
    Q_OBJECT
public:
    explicit TileMap(QObject *parent = 0);
    //explicit TileMap(QGraphicsScene* s);
    QList<Tile*> storage;
    QVector<QVector<bool> > matrix;

    void drawField(uint width, uint height, QPoint center);
    void drawViewField(QRect r);
    void init();
    void setScene(QGraphicsScene *s);
    void setView(QGraphicsView *v);
    void setPreviewView(PreviewView* pv);
    void setScale(QSize &size, uint s);
    void setImgSizes(QVector<QSize> ims);
    void setTileAmount(QVector<QSize> ta);
    void viewSizeChanged(QRect r);
    void clear(QRect r);
    void clearAll();
    ~TileMap();
    int memStatus();
    void loadImage(QDir p);
private:
    QSize view_size;
    QSize tile_size;
    QSize map_size;
    QSize result_size;
    QRect rect;
    QGraphicsScene* scene;
    QGraphicsView* view;
    PreviewView* preview;
    uint scale;
    QString image_path;
    QRect getViewField();
    QPoint getCentralPoint();
    QVector<QSize> imgSizes;
    QVector<QSize> tileAmount;
private slots:
    void viewResized();


    void scrolledVertical(int value);

    void scrolledHorizontal(int value);

    void zoomOut(QPoint pnt);
    void zoomIn(QPoint pnt);
signals:
    void viewRect(QRect r);
    void topLeftPointEvent(QPointF);
    void scaleChanged(uint scale);
public slots:
    void updateItems();

};

#endif // TILEMAP_H
