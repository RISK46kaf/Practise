#ifndef VIEWERSMANAGER_H
#define VIEWERSMANAGER_H

#include <QObject>
#include <QVector>
#include <QSize>
#include <QPoint>
#include <QPointF>
#include <QRect>

namespace MyViewers {

class MyGraphicsView;
class TileMap;

}

namespace Figures {

class FiguresManager;

}

class QTimer;
class QGraphicsScene;
class QListWidgetItem;
class QHBoxLayout;
class QWidget;

namespace Core
{

class ViewersManager : public QObject
{
    Q_OBJECT
public:
    explicit ViewersManager(QHBoxLayout* layout,QWidget* holder ,QObject *parent = 0);

    void on_actionLoad_Image();
    void on_imageListWidget_currentRowChanged(int currentRow);
    Figures::FiguresManager* figuresManager();
private:
    MyViewers::MyGraphicsView* _view;
    MyViewers::TileMap* _map;
    QStringList _paths;
    uint _oldValueHorizontal;
    uint _oldValueVertical;
    uint _scale;
    QVector<QSize> _imgSizes;
    QVector<QSize> _tileAmount;
    QSize _map_size;
    QStringList _imageList;
    QGraphicsScene* _cmpScene;
    QVector<QListWidgetItem*> _items;
    QTimer* _t;
    bool _l;
    QGraphicsScene* _scene;
    QHBoxLayout* _layoutView;
    QWidget* _holder;
    Figures::FiguresManager* _figuresManager;

private:
    QRect getViewField();
    QPoint getCentralPoint();
    void setXML(QString path);
    void setMousePos(QPoint pnt);

private slots:

    void viewResized();

    void viewChanged();

    void scrolledVertical(int value);

    void scrolledHorizontal(int value);

    void zoomOut(QPoint pnt);
    void zoomIn(QPoint);

    void timeout();

    void setViewPos(QPointF pnt);
    void calcDx(int);
    void calcDy(int);


signals:
    void topLeftPointEvent(QPointF);
    void viewRect(QRect r);
};

}
#endif // VIEWERSMANAGER_H
