#ifndef SELECTOR_H
#define SELECTOR_H

#include <QMainWindow>
#include "shape.h"

class Storage;
class RecognizeMediator;
//class Arrow;
//class Rect;
//class Ellipse;
//class Polygon;

namespace Ui {
class Selector;
}

class Selector : public QMainWindow
{
    Q_OBJECT

public:
    explicit Selector(QWidget *parent = 0);
    ~Selector();

public slots:
    void openImage();
    void autoZoom();
private:
    Ui::Selector *ui;
    void init();
    Storage *_storage;
    QSize _storage_size;
    void zoomChange(bool in);
    QPixmap _image;
    QList<Arrow> *_arrow_list;
    QList<Rect> *_rect_list;
    QList<Ellipse> *_ellipse_list;
    QList<Polygon> *_polygon_list;
    RecognizeMediator* _mediator;
};

#endif // SELECTOR_H
