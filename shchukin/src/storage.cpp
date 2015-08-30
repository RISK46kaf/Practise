#include "storage.h"
#include <QDebug>
#include <QScrollArea>
#include <QScrollBar>
#include "math.h"

///
/// \brief The Storage class класс области содержащей изображение
///
Storage::Storage(QWidget *parent) :
    QLabel(parent)
{
    arrow_size_ = 20;
//    view_labels_ = 1;
//    view_current_l_ = 0;
//    set_label_width_ = 0;
    repaint_needed_ = 0;
//    confirm_nothing_tools_ = 1;
//    change_ = 0;
//    change_ID_= -1 ;
    tool_ = NoTool;
    state_ = StandBy;
    keyboard_modifier_ = Qt::NoModifier;
    m_last_poly = true;

//    focused_selection_ = -1;
//    focused_label_ID_selection_ = -1;
//    focused_selection_type_ = NoFigure;

//    hovered_point_.figure = NoFigure;
//    hovered_point_.figureID = -1;
//    hovered_point_.pointID = -1;

//    selected_point_ = -1;
//    list_bounding_box_ = 0;
//    point_radius_ = 6;
    scale_=1;
    setScaledContents(true);
    setMouseTracking(true);

    setScaledContents(true); // можно масштабировать контенд
    scale_ = 1; // переменная, хранящая масштаб
}
///
/// \brief scaleStorage функция сканирования
/// \param aDirection тип зума
/// \param scaleFactor масштаб
///
void Storage::scaleStorage(ZoomType aDirection, const double &scaleFactor)
{
    scale_ = 1;
    QSize size = this->size();
    qDebug() << "2" << size;
    switch (aDirection) {
    case ZoomIn:
        size *= scaleFactor;
        scale_ *= scaleFactor;
        break;
    case ZoomOut:
        size /= scaleFactor;
        scale_ /= scaleFactor;
        break;
    case NoZoom:
        return;
    default:
        break;
    }
    qDebug() << "3" << size;
    this->resize(size);
    qDebug() << "scaled?" << this->hasScaledContents();
    qDebug() << "4" << this->size();
}


void Storage::setScrollArea(QScrollArea *aPointer)
{
    if (0 == aPointer) {
        return;
        /* NOTREACHED */
    }

    scroll_area_ = aPointer;
}

void Storage::setArrows(QList<Arrow> *listOfArrows)
{
    _arrow_list = listOfArrows;
}

void Storage::setRects(QList<Rect> *listOfRects)
{
    _rect_list = listOfRects;
}

void Storage::setEllipses(QList<Ellipse> *listOfEllipses)
{
    _ellipse_list = listOfEllipses;
}

void Storage::setPolygons(QList<Polygon> *listOfPolygons)
{
    _polygon_list = listOfPolygons;
}

void Storage::setTool(Tool aTool)
{
//    confirm_nothing_tools_ = 0;
    switch(aTool) {
    case BoundingBoxTool:
        tool_ = BoundingBoxTool;
        break;
    case PolygonTool:
        tool_ = PolygonTool;
        break;
    case EllipseTool:
        tool_ = EllipseTool;
        break;
    case ArrowTool:
        tool_ = ArrowTool;

        break;
    default:
        tool_ = NoTool;
        break;
    }
    qDebug() << tool_;
}

void Storage::triggerPolygon(
    const QPoint &aPoint,
    Polygon &aNewPoly
    )
{
    QPolygon tmp = aNewPoly.getCoordinates();
    tmp << aPoint;
    aNewPoly.setCoordinates(tmp);

    repaint_needed_ = 1;
}

void Storage::mousePressEvent(QMouseEvent *anEvent)
{
    /* запоминаем координаты клика */
    prev_cursor_pos_ = anEvent->pos() / scale_;

    QPoint pos = anEvent->pos() / scale_;

    if (anEvent->buttons() & Qt::LeftButton) {
        /* очищаем выбранную область если она не была подтверждена(для прямоугольника) */
        if (NewSelection == state_ && BoundingBoxTool == tool_) {
            rect.setCoordinates(QRect(-1, -1, 0, 0));
            state_ = StandBy;
        }
        /* очищаем выбранную область если она не была подтверждена(для эллипса) */
        if (NewSelection == state_ && EllipseTool == tool_) {
            ell.setCoordinates(QRect(-1, -1, 0, 0));
            state_ = StandBy;
        }
        /* очищаем выбранную область если она не была подтверждена(для стрелы) */
        if (NewSelection == state_ && ArrowTool == tool_) {
            arrow.setCoordinates(QLineF(-1, -1, -2, -2));
            state_ = StandBy;
        }

        /* добавляем новые точки для многоугольника */
        if (PolygonTool == tool_ &&
            NewSelection == state_ &&
            Qt::NoModifier == keyboard_modifier_)
        {
            triggerPolygon(pos, poly);
        }

        /* начинаем выбирать новую область по клику */
        if (StandBy == state_ && NoTool != tool_ /*&&
            -1 == focused_selection_*/) {
            state_ = NewSelection;
//            emit selectionStarted();

            poly.setCoordinates(QPolygon());
            if (PolygonTool == tool_) {
//                QPolygon tP = poly.getCoordinates();
//                tP  ;

                poly.setCoordinates(poly.getCoordinates() << prev_cursor_pos_ << pos);
//                polygon_.poly << prev_cursor_pos_;
            }
        }

        /* выбираем точку */
//        selected_point_ = -1;
        repaint_needed_ = 1;
//        if (-1 != hovered_point_.figureID &&
//            !list_polygon_->isEmpty() &&
//            PolyFigure == hovered_point_.figure &&
//            hovered_point_.figureID == focused_selection_)
//        {
//            selected_point_ = hovered_point_.pointID;
//
    }
//    }

    if (repaint_needed_) {
        update();
        repaint_needed_ = 0;
    }
}


void Storage::mouseReleaseEvent(QMouseEvent *anEvent)
{
    Q_UNUSED(anEvent)
    last_tool_ = tool_;

//    confirm_nothing_tools_ = false;
//    if (-1 != hovered_point_.figureID)
//        emit areaEdited();

//    if (RectFigure == hovered_point_.figure &&
//        -1 != hovered_point_.figureID &&
//        !list_bounding_box_->
//            at(hovered_point_.figureID)->
//            rect.isValid()
//        )
//    {
//        BoundingBox *rect = list_bounding_box_->at(hovered_point_.figureID);
//        rect->rect = rect->rect.normalized();
//    }
//    if (EllipseFigure == hovered_point_.figure &&
//            -1 != hovered_point_.figureID &&
//            !list_ellipse_->
//                at(hovered_point_.figureID)->
//            rect.isValid()
//        )
//    {
//        Ellipse *ell = list_ellipse_->at(hovered_point_.figureID);
//        ell->rect = ell->rect.normalized();
//    }
}

void Storage::triggerBoundBox(
    const QPoint &aNewPos,
    const QPoint &anOldPos,
    Rect &aNewRect
    )
{
    QRect tmp;
    tmp.setCoords(
                anOldPos.x(),
                anOldPos.y(),
                aNewPos.x(),
                aNewPos.y()
                );
    aNewRect.setCoordinates(tmp);

    state_ = NewSelection;
    repaint_needed_ = 1;
}

void Storage::triggerEllipse(
    const QPoint &aNewPos,
    const QPoint &anOldPos,
    Ellipse &aNewEll
    )
{
    QRect tmp;
    tmp.setCoords(
                anOldPos.x(),
                anOldPos.y(),
                aNewPos.x(),
                aNewPos.y()
                );
    aNewEll.setCoordinates(tmp);

    state_ = NewSelection;
    repaint_needed_ = 1;
}


void Storage::triggerArrow(
    const QPoint &aNewPos,
    const QPoint &anOldPos,
    Arrow &aNewArrow
    )
{
    QLineF aNewLine;
    aNewLine.setLine(
             anOldPos.x(),
             anOldPos.y(),
             aNewPos.x(),
             aNewPos.y()
    );
    aNewArrow.setCoordinates(aNewLine);
    state_ = NewSelection;
    repaint_needed_ = 1;
}

void Storage::mouseMoveEvent(QMouseEvent *anEvent)
{
    QPoint pos = anEvent->pos() / scale_;
//    QPolygon tPoly(poly.getCoordinates());
//    int tInt;
//    if(1 < (tInt = tPoly.count()) )
//    {
//        if(m_last_poly)
//            tPoly.append(pos);
//        tPoly.setPoint(tInt,pos);
//        poly.setCoordinates(tPoly);
//        update();
//    }
    if (anEvent->pos().x() < 0)
        pos.setX(0);

    if (width() < anEvent->pos().x())
        pos.setX(width() - 1);

    if (anEvent->pos().y() < 0)
        pos.setY(0);


    if (height() < anEvent->pos().y())
        pos.setY(height() - 1);

    /* изменяем прямоугольник  */
    if ((anEvent->buttons() & Qt::LeftButton) &&
        BoundingBoxTool == tool_ &&
        NewSelection == state_ &&
        Qt::NoModifier == keyboard_modifier_)
    {
        triggerBoundBox(pos, prev_cursor_pos_, rect);
    }

    /* изменяем эллипс  */
    if ((anEvent->buttons() & Qt::LeftButton) &&
        EllipseTool == tool_ &&
        NewSelection == state_ &&
        Qt::NoModifier == keyboard_modifier_)
    {
        triggerEllipse(pos, prev_cursor_pos_, ell);
    }

    /* изменяем стрелу  */
    if ((anEvent->buttons() & Qt::LeftButton) &&
        ArrowTool == tool_ &&
        NewSelection == state_ &&
        Qt::NoModifier == keyboard_modifier_)
    {
        triggerArrow(pos, prev_cursor_pos_, arrow);
    }

    /* перемещаем последнюю точку(курсор) многоугольника до создания(точка зафиксирется кликом) новой */
    if (PolygonTool == tool_ &&
        NewSelection == state_ &&
        (anEvent->buttons() & Qt::LeftButton))
    {
        QPolygon tmp = poly.getCoordinates();
        tmp.setPoint(tmp.count() - 1, pos);
        poly.setCoordinates(tmp);
        repaint_needed_ = 1;
        m_last_poly = true;
    }
    /* когда изображение слишком большое(необходима прокрутка) */
    if ((anEvent->buttons() & Qt::MiddleButton) &&
        (scroll_area_->size().height() < size().height() ||
        scroll_area_->size().width() < size().width()))
    {
        QPoint globPos = mapToGlobal(pos);
        QPoint prev = mapToGlobal(prev_cursor_pos_);
        int horValue = scroll_area_->horizontalScrollBar()->value();
//        scroll_area_->horizontalScrollBar()
        int verValue = scroll_area_->verticalScrollBar()->value();


        QPoint delta = globPos - prev;
        prev_cursor_pos_ = pos;

        horValue += delta.x();
        verValue += delta.y();

        scroll_area_->horizontalScrollBar()->setValue(horValue);
        scroll_area_->verticalScrollBar()->setValue(verValue);
    }

    if (repaint_needed_) {
        update();
        repaint_needed_ = 0;
    }
}

void Storage::paintEvent(QPaintEvent *anEvent)
{
    QLabel::paintEvent(anEvent);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPen pen;

    if (NoTool != tool_) {
        pen.setWidth(5);
        pen.setColor(QColor(Qt::white));
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);

        if (BoundingBoxTool == tool_) {
            /* с учётом масштаба */
            QRect bbox = rect.getCoordinates();
            QPoint bboxTopLeft = bbox.topLeft() * scale_;
            QPoint bboxBottomRight = bbox.bottomRight() * scale_;

            bbox.setTopLeft(bboxTopLeft);
            bbox.setBottomRight(bboxBottomRight);

            painter.drawRect(bbox);
        }
        else if (EllipseTool == tool_) {
            /* с учётом масштаба */
            QRect elli = ell.getCoordinates().normalized();
            QPoint ellTopLeft = elli.topLeft() * scale_;
            QPoint ellBottomRight = elli.bottomRight() * scale_;

            elli.setTopLeft(ellTopLeft);
            elli.setBottomRight(ellBottomRight);

            if(1 < elli.height() && 1 < elli.width() )
            {
                painter.drawEllipse(elli);
            }
//            painter.drawRect(ell);
        }
        else if (ArrowTool == tool_) {
            /* с учётом масштаба */
            QLineF line = arrow.getCoordinates();
            QPointF p1 = line.p1() * scale_;
            QPointF p2 = line.p2() * scale_;

            line.setP1(p1);
            line.setP2(p2);

            if(1 < line.length())
            {
                double angle = ::acos(line.dx() / line.length());
                qreal Pi = atan(1)*4;
                if (line.dy() >= 0)
                    angle = (Pi * 2) - angle;

                QPointF arrowP1 = line.p1() + QPointF(sin(angle + Pi / 3) * arrow_size_,
                                                cos(angle + Pi / 3) * arrow_size_);
                QPointF arrowP2 = line.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrow_size_,
                                                cos(angle + Pi - Pi / 3) * arrow_size_);

                QPolygonF arrowTop;
                arrowTop.clear();
                arrowTop << line.p1() << arrowP1 << arrowP2;

                painter.drawLine(line);
                painter.drawPolygon(arrowTop);///111
                qDebug() << "arrowTop" << arrowTop;
                arrow_top_ = arrowTop;
            }

            }
        else if (PolygonTool == tool_) {
            /* с учётом масштаба */
            QPoint point;
            QPolygon pol = poly.getCoordinates();
            for (int i = 0; i < pol.size(); i++) {
                point.setX(pol.at(i).x());
                point.setY(pol.at(i).y());
                point *= scale_;
                pol.remove(i);
                pol.insert(i, point);
            }
            painter.drawPolygon(pol);
        }
    }

    /* рисуем фигуры */
    drawBoundingBoxes(&painter, &pen);
    drawPolygons(&painter, &pen);
    drawEllipses(&painter, &pen);
    drawArrows(&painter, &pen);
}

//! рисуется только после подтверждения выбранной прямоугольной области
/*!
 * Шаг 6 в выделении области
 */
void Storage::drawBoundingBoxes(
    QPainter *aPainter,
    QPen *aPen
) const
{
    if (0 == _rect_list)
    {
        return;
        /* NOTREACHED */
    }

    Qt::PenStyle penStyle;
    int width = 2;
    /* рисуем все прямоугольники */
    for (int i = 0; i < _rect_list->size(); i++) {
        penStyle = Qt::SolidLine;
        int labelID = _rect_list->at(i).getEvidenceID();

        /* масштабируем */
        QRect _rec = _rect_list->at(i).getCoordinates().normalized();// list_bounding_box_->at(i)->rect.normalized();
        QPoint topLeft = _rec.topLeft() * scale_;
        QPoint bottomRight = _rec.bottomRight() * scale_;

        _rec.setTopLeft(topLeft);
        _rec.setBottomRight(bottomRight);

        aPen->setWidth(width);
        aPen->setStyle(penStyle);
        aPainter->setPen(*aPen);

        aPainter->drawRect(_rec);

        /*подписываем ID*/
        QString labelIDText =
            QString("%1").arg(labelID);

        aPainter->drawText(
            _rec.left() + 5,
            _rec.top() + 5,
            20,
            20,
            Qt::AlignLeft,
            labelIDText
            );
    }

}

//! рисуется только после подтверждения выбранной многоугольной области
/*!
 * Шаг 6 в выделении области
 */
void Storage::drawPolygons(
    QPainter *aPainter,
    QPen *aPen
) const
{
    if (NULL == _polygon_list)
    {
        return;
        /* NOTREACHED */
    }

    Qt::PenStyle penStyle = Qt::SolidLine;
    int width = 2;
    /* рисуем все многоугольники */
    for (int i = 0; i < _polygon_list->size(); i++) {
        penStyle = Qt::SolidLine;
        int labelID = _polygon_list->operator [](i).getEvidenceID();

        /* настраиваем цвет для лкйбла к которому относится выделенная область */
        aPen->setColor(QColor(_polygon_list->operator [](i).getColor()));

        /* меняем стиль линии и толщину если текущая область выбрана(для изменения) */
//        if (PolyFigure == focused_selection_type_ &&
//            focused_selection_ == i) {
//            penStyle = Qt::DotLine;
//            width = 3;
//        }

        QPoint point;
        QPolygon _pol = _polygon_list->operator [](i).getCoordinates();
        for (int j = 0; j < _pol.size(); j++) {
            point.setX(_pol.at(j).x());
            point.setY(_pol.at(j).y());
            /* масштабируем */
            point *= scale_;
            _pol.remove(j);
            _pol.insert(j, point);


//            if (focused_selection_ == i &&
//                focused_selection_type_ == PolyFigure) {
//                QPen circPen;
//                circPen.setWidth(2);
//                circPen.setStyle(Qt::SolidLine);
//                circPen.setColor(aPen->color());
//                aPainter->setPen(circPen);
//                /* если точка неподтвержденная(меняем область) то делаем ее стиллистически заметной */
//                if ((j == hovered_point_.pointID &&
//                    i == hovered_point_.figureID &&
//                    PolyFigure == hovered_point_.figure) ||
//                    j == selected_point_) {
//                    QBrush brush;
//                    brush.setColor(aPen->color());
//                    brush.setStyle(Qt::SolidPattern);
//                    aPainter->setBrush(brush);
//                }
//                aPainter->drawEllipse(point, point_radius_, point_radius_);
//                aPainter->setBrush(Qt::NoBrush);
//            }
        }

//        if(set_label_width_)
//        {
//            qDebug() <<list_width_->size();
//            for(int j=0; j<list_width_->size();++j)
//            {
//                if(list_width_->at(j).label_ID_== labelID)
//                {
//                    width = list_width_->at(j).new_width_;
//                }
//            }
//        }
        aPen->setWidth(width);
        aPen->setStyle(penStyle);
//        if(!view_labels_)
//        {
//            qDebug() << "лейблы не видны?";
//            aPen->setStyle(Qt::NoPen);
//        }
////        qDebug() << view_current_l_;
//        if(view_current_l_)
//        {
//            if(labelID!= *label_ID_)
//            {
//                qDebug() << "лейблы не видны?";
//                aPen->setStyle(Qt::NoPen);
//            }
//            qDebug() << "ok?";
//        }
//        qDebug() << *label_ID_;
        aPainter->setPen(*aPen);

        aPainter->drawPolygon(_pol);
        /*подписываем ID*/
        QString labelIDText =
            QString("%1").arg(labelID);
        QRect _rect = _pol.boundingRect();
        int x = _rect.center().x();
        int y = _rect.center().y();

        aPainter->drawText(
            x,
            y,
            20,
            20,
            Qt::AlignHCenter,
            labelIDText
            );
    }

}


//! рисуется только после подтверждения выбранной эллипсоидной области
/*!
 * Шаг 6 в выделении области
 */
void Storage::drawEllipses(
    QPainter *aPainter,
    QPen *aPen
) const
{
    if (0 == _ellipse_list)
    {
        return;
        /* NOTREACHED */
    }

    Qt::PenStyle penStyle;
    int width = 2;
    /* рисуем все эллипсы */
    for (int i = 0; i < _ellipse_list->size(); i++) {
        penStyle = Qt::SolidLine;
        int labelID = _ellipse_list->operator [](i).getEvidenceID();

        /* настраиваем цвет для лкйбла к которому относится выделенная область */
//        if (labelID < list_label_color_->count())
//            aPen->setColor(QColor(list_label_color_->at(labelID)));
//        /* в случае если нет цвета для текущего лейбла */
//        else
//            aPen->setColor(QColor(Qt::white));
        _ellipse_list->operator [](i).getColor();

        /* меняем стиль линии и толщину если текущая область выбрана(для изменения) */
//        if (EllipseFigure == focused_selection_type_ &&
//            focused_selection_ == i) {
//            penStyle = Qt::DotLine;
//            width = 3;
//        }

        /* масштабируем */
        QRect _elli = _ellipse_list->operator [](i).getCoordinates().normalized();
                //->at(i)->rect.normalized();
        QPoint topLeft = _elli.topLeft() * scale_;
        QPoint bottomRight = _elli.bottomRight() * scale_;

        _elli.setTopLeft(topLeft);
        _elli.setBottomRight(bottomRight);
//        if (focused_selection_ == i &&
//            focused_selection_type_ == EllipseFigure) {
//            QPen circPen;
//            circPen.setWidth(2);
//            circPen.setStyle(Qt::SolidLine);
//            circPen.setColor(aPen->color());
//            aPainter->setPen(circPen);
//            for (int j = 0; j < 4; j++) {
//                QPoint point;
//                /* по номеру точки записаннму при кликах получаем вершины прямоугольника */
//                if (!j) {
//                    point = ell.topLeft();
//                }
//                else if (1 == j)
//                {
//                    point = ell.topRight();
//                }
//                else if (2 == j)
//                {
//                    point = ell.bottomRight();
//                }
//                else if (3 == j)
//                {
//                    point = ell.bottomLeft();
//                }
//                /* если точка неподтвержденная(меняем область) то делаем ее стиллистически заметной */
//                if (i == hovered_point_.figureID &&
//                    j == hovered_point_.pointID &&
//                    EllipseFigure == hovered_point_.figure) {
//                    QBrush brush;
//                    brush.setColor(aPen->color());
//                    brush.setStyle(Qt::SolidPattern);
//                    aPainter->setBrush(brush);
//                }
//                aPainter->drawEllipse(point, point_radius_, point_radius_);
//                aPainter->setBrush(Qt::NoBrush);
//            }
//        }
//        if(set_label_width_)
//        {
//            qDebug() <<list_width_->size();
//            for(int j=0; j<list_width_->size();++j)
//            {
//                if(list_width_->at(j).label_ID_== labelID)
//                {
//                    width = list_width_->at(j).new_width_;
//                }
//            }
//        }

        aPen->setWidth(width);
        aPen->setStyle(penStyle);
//        if(!view_labels_)
//        {
//            qDebug() << "лейблы не видны?";
//            aPen->setStyle(Qt::NoPen);
//        }
////        qDebug() << view_current_l_;
//        if(view_current_l_)
//        {
//            if(labelID!= *label_ID_)
//            {
//                qDebug() << "лейблы не видны?";
//                aPen->setStyle(Qt::NoPen);
//            }
//            qDebug() << "ok?";
//        }
//        qDebug() << *label_ID_;
        aPainter->setPen(*aPen);

        aPainter->drawEllipse(_elli);

        /*подписываем ID*/
        QString labelIDText =
            QString("%1").arg(labelID);

        aPainter->drawText(
            _elli.left() + 5,
            _elli.top() + 5,
            20,
            20,
            Qt::AlignLeft,
            labelIDText
            );
    }

}

void
Storage::drawArrows(
    QPainter *aPainter,
    QPen *aPen
) const
{
    if (0 == _arrow_list)
    {
        return;
        /* NOTREACHED */
    }

    Qt::PenStyle penStyle;
    int width = 2;
    /* рисуем все эллипсы */
    for (int i = 0; i < _arrow_list->size(); i++) {
        penStyle = Qt::SolidLine;
        int labelID = _arrow_list->operator [](i).getEvidenceID();

        /* настраиваем цвет для лкйбла к которому относится выделенная область */
//        if (labelID < list_label_color_->count())
//            aPen->setColor(QColor(list_label_color_->at(labelID)));
//        /* в случае если нет цвета для текущего лейбла */
//        else
//            aPen->setColor(QColor(Qt::white));
        aPen->setColor(QColor(_arrow_list->operator [](i).getColor()));

        /* меняем стиль линии и толщину если текущая область выбрана(для изменения) */
//        if (ArrowFigure == focused_selection_type_ &&
//            focused_selection_ == i) {
//            penStyle = Qt::DotLine;
//            width = 3;
//        }

        /* масштабируем */
        QLineF _line = _arrow_list->operator [](i).getCoordinates();
        QPointF p1 = _line.p1() * scale_;
        QPointF p2 = _line.p2() * scale_;

        _line.setP1(p1);
        _line.setP2(p2);
//        if (focused_selection_ == i &&
//            focused_selection_type_ == ArrowFigure) {
//            QPen circPen;
//            circPen.setWidth(2);
//            circPen.setStyle(Qt::SolidLine);
//            circPen.setColor(aPen->color());
//            aPainter->setPen(circPen);
//            for (int j = 0; j < 2; j++) {
//                QPointF point;
//                /* по номеру точки записаннму при кликах получаем вершины прямоугольника */
//                if (!j) {
//                    point = line.p1();
//                }
//                else if (1 == j)
//                {
//                    point = line.p2();
//                }
//                /* если точка неподтвержденная(меняем область) то делаем ее стиллистически заметной */
//                if (i == hovered_point_.figureID &&
//                    j == hovered_point_.pointID &&
//                    ArrowFigure == hovered_point_.figure) {
//                    QBrush brush;
//                    brush.setColor(aPen->color());
//                    brush.setStyle(Qt::SolidPattern);
//                    aPainter->setBrush(brush);
//                }
//                aPainter->drawEllipse(point, point_radius_, point_radius_);
//                aPainter->setBrush(Qt::NoBrush);
//            }
//        }
//        if(set_label_width_)
//        {
//            qDebug() <<list_width_->size();
//            for(int j=0; j<list_width_->size();++j)
//            {
//                if(list_width_->at(j).label_ID_== labelID)
//                {
//                    width = list_width_->at(j).new_width_;
//                }
//            }
//        }

        aPen->setWidth(width);
        aPen->setStyle(penStyle);
//        if(!view_labels_)
//        {
//            qDebug() << "лейблы не видны?";
//            aPen->setStyle(Qt::NoPen);
//        }
////        qDebug() << view_current_l_;
//        if(view_current_l_)
//        {
//            if(labelID!= *label_ID_)
//            {
//                qDebug() << "лейблы не видны?";
//                aPen->setStyle(Qt::NoPen);
//            }
//            qDebug() << "ok?";
//        }
//        qDebug() << *label_ID_;
        aPainter->setPen(*aPen);

//        aPainter->drawEllipse(line);
        ///222

        double angle = ::acos(_line.dx() / _line.length());
        qreal Pi = atan(1)*4;
        if (_line.dy() >= 0)
            angle = (Pi * 2) - angle;

        QPointF arrowP1 = _line.p1() + QPointF(sin(angle + Pi / 3) * arrow_size_,
                                        cos(angle + Pi / 3) * arrow_size_);
        QPointF arrowP2 = _line.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrow_size_,
                                        cos(angle + Pi - Pi / 3) * arrow_size_);

        QPolygonF arrowTop;
        arrowTop.clear();
        arrowTop << _line.p1() << arrowP1 << arrowP2;

        aPainter->drawLine(_line);
        qDebug() << "arrow_top_" << arrow_top_;
        aPainter->drawPolygon(arrowTop);

        /*подписываем ID*/
        QString labelIDText =
            QString("%1").arg(labelID);

        aPainter->drawText(
            _line.p2().x() + 5,
            _line.p2().y() + 5,
            20,
            20,
            Qt::AlignLeft,
            labelIDText
            );
    }

}

bool Storage::confirmSelection()
{
    if (BoundingBoxTool == last_tool_) {
        Rect *_bbox = new Rect;
        rect.setCoordinates(rect.getCoordinates().normalized());
        *_bbox = rect;
        _rect_list->append(*_bbox);
        rect.setCoordinates(QRect(-1, -1, 0, 0));
        state_ = StandBy;
        update();
        return true;
    }
    else if (PolygonTool == last_tool_) {
        Polygon *_pol = new Polygon;
        *_pol = poly;
        _polygon_list->append(*_pol);
        poly.setCoordinates(QPolygon());
        state_ = StandBy;
        update();
        return true;
    }
    else if (EllipseTool == last_tool_) {
        Ellipse *_ell = new Ellipse;
        ell.setCoordinates(ell.getCoordinates().normalized());
        *_ell = ell;
        _ellipse_list->append(*_ell);
        ell.setCoordinates(QRect(-1, -1, 0, 0));
        state_ = StandBy;
        update();
        return true;
    }
    else if (ArrowTool == last_tool_) {
        Arrow *_arrow = new Arrow;
        *_arrow = arrow;
        _arrow_list->append(*_arrow);
        arrow.setCoordinates(QLineF(-1, -1, -2, -2));
        state_ = StandBy;
        update();
        return true;
    }
    return false;
}
