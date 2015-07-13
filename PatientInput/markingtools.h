#ifndef MarkingTools_H
#define MarkingTools_H

#include <QMainWindow>
#include <QFileDialog>
#include <QScrollBar>
#include "shape.h"

class Storage;

namespace Ui {
class MarkingTools;
}

class MarkingTools : public QMainWindow
{
    Q_OBJECT

public:
    explicit MarkingTools(QWidget *parent = 0);
    void setImage(QPixmap);

    ~MarkingTools();
private slots:
    void on_actionOpen_triggered();

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_actionZoomAuto_triggered();

    void on_actionEllipse_toggled(bool arg1);

    void on_actionRect_toggled(bool arg1);

    void on_actionPolygon_toggled(bool arg1);

    void on_actionArrow_toggled(bool arg1);

    void on_checkPartBox_toggled(bool checked);

private:
    Storage *storage_;
    QSize storage_size_;
    void openImage();
    void autoZoom();
    void zoomChange(bool in);
    QPixmap _image;
    void enableDefineButtons();
    void disableDefineButtons();
    QList<Arrow> *_arrow_list;
    QList<Rect> *_rect_list;
    QList<Ellipse> *_ellipse_list;
    QList<Polygon> *_polygon_list;
    QStringList *_praparation_list;
    QStringList *_dye_list;
    QString _diagrosis;
    QString _d_rate;
    QString _praparation;
    QString _dye;
    QString _pic_zoom;
private:
    Ui::MarkingTools *ui;
};

#endif // MarkingTools_H
