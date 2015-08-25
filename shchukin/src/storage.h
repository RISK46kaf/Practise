#ifndef STORAGE_H
#define STORAGE_H

#include <QLabel>
#include <QScrollArea>
#include "shape.h"
#include <QMouseEvent>


enum Tool {
    NoTool,
    BoundingBoxTool,
    PolygonTool,
    EllipseTool,
    ArrowTool
};

///
/// \brief The ZoomType enum NoZoom = x 1, ZoomIn = x scale, ZoomOut = / scale
///
enum ZoomType {
    NoZoom, // *1
    ZoomIn, // *scale
    ZoomOut // /scale
};
///
/// \brief The Storage class класс области содержащей изображение
///
class Storage : public QLabel
{
    Q_OBJECT

    QList<Arrow> *_arrow_list;
    QList<Rect> *_rect_list;
    QList<Ellipse> *_ellipse_list;
    QList<Polygon > *_polygon_list;
    QStringList *_praparation_list;
    QStringList *_dye_list;
    Tool tool_;
    void triggerPolygon(
        const QPoint &aPoint,
        Polygon &aNewPoly
        );
    void triggerBoundBox(
            const QPoint &aNewPos,
            const QPoint &anOldPos,
            Rect &aNewRect
            );
    void triggerEllipse(
        const QPoint &aNewPos,
        const QPoint &anOldPos,
        Ellipse &aNewEll
        );
    void triggerArrow(
        const QPoint &aNewPos,
        const QPoint &anOldPos,
        Arrow &aNewArrow
        );

    void
    drawBoundingBoxes(
        QPainter *aPainter,
        QPen *aPen
    ) const;
    void
    drawPolygons(
        QPainter *aPainter,
        QPen *aPen
    ) const;
    void
    drawEllipses(
        QPainter *aPainter,
        QPen *aPen
    ) const;
    void
    drawArrows(
        QPainter *aPainter,
        QPen *aPen
    ) const;



    double scale_;
public:

    enum State {
        StandBy,
        NewSelection
    };

    explicit Storage(QWidget *parent = 0);
    ///
    /// \brief scaleStorage функция сканирования
    /// \param aDirection тип зума
    /// \param scaleFactor масштаб
    ///
    void scaleStorage(ZoomType aDirection, const double &scaleFactor);
    void setArrows(QList<Arrow> *);
    void setRects(QList<Rect> *);
    void setEllipses(QList<Ellipse> *);
    void setPolygons(QList<Polygon> *);
    void setPreparations(QStringList *);
    void setDyes(QStringList *);
    void setTool(Tool aTool);
    QPoint prev_cursor_pos_;
    bool m_last_poly;
    Arrow arrow;
    Rect rect;
    Ellipse ell;
    Polygon poly;
    State state_;
    bool repaint_needed_;
    int keyboard_modifier_;
    QScrollArea *scroll_area_;
    bool confirmSelection();
    qreal arrow_size_;
    QPolygonF arrow_top_;
    void setScrollArea(QScrollArea *aPointer);
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *anEvent);
signals:

public slots:

};

#endif // STORAGE_H
