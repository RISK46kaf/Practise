#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include "tilemap.h"
#include "mygraphicsview.h"
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QScrollBar>
#include <QXmlStreamReader>
#include <ImageFrame/Preview/previewview.h>
#include <QListWidget>
#include "Markers/marker.h"
#include "mygraphicsscene.h"
#include <QGridLayout>
#include <QPushButton>
#include <QObject>
#include <QLabel>
#include <QTextEdit>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);
    MyGraphicsView* view;
    PreviewView* preview;
    MyGraphicsScene* scene;
    QGraphicsScene* previewScene;
    TileMap* map;
    QVector<Marker*> markers;
    uint scale;
    void openByName(const QString& filename);
    QString getFilename() const;
    QString getPath() const;

private:
    QGridLayout* layout;
    QVBoxLayout* subLayout;
    QLabel*      comenLab;
    QTextEdit*   textComen;
    QPushButton* openButton;

    QGraphicsPixmapItem *centralItem;
    QStringList paths;
    uint oldValueHorizontal;
    uint oldValueVertical;
    QRect old_view_field;
    QSize map_size;
    QRect getViewField();
    QPoint getCentralPoint();
    QStringList imageList;
    QVector<QListWidgetItem*> items;
    QTimer* t;
    QString filename;
    QString path;


    void setXML(QString path);
    void setPreview(QString path);
    void setMousePos(QPoint pnt);
    bool l;
public slots:
    void markerScaleChange(uint sc);
    void openImage(bool);

private slots:
    void setViewPos(QPointF pnt);

signals:
    void topLeftPointEvent(QPointF);
    void viewRect(QRect r);
};

#endif // IMAGEWIDGET_H
