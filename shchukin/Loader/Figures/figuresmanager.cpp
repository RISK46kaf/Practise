#include "figuresmanager.h"

#include "arrow.h"
#include "ellipse.h"
#include "polygon.h"
#include "rect.h"


#include <math.h>
#include <QPainter>
#include <QPen>
#include <QScrollArea>
#include <QScrollBar>
#include <QPainter>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

namespace Figures {

QMap<FigureType,QString> FigureTypeStr{
    {FigureType::NoFigure, "nope"},
    {FigureType::ArrowFigure, "arrow"},
    {FigureType::EllipseFigure, "ellipse"},
    {FigureType::PolygonFigure, "polygon"},
    {FigureType::RectFigure, "rectangle"}
};


FiguresManager::FiguresManager(QObject *parent) : QObject(parent),
    m_id(-1),m_last_mark_id(-1),m_tool(Tool::NoTool), m_temp_figure(NULL), m_new_selection(0), m_vertical_scroll(NULL),
    m_horizontal_scroll(NULL),_scale(0),_curr_color(NULL),_dx(0),_dy(0)
{
}

FiguresManager::FiguresManager(const FiguresManager &other) : QObject(0),
    m_id(other.m_id), m_tool(other.m_tool), m_temp_figure(NULL), m_figures(other.m_figures),
    m_new_selection(other.m_new_selection), m_vertical_scroll(other.m_vertical_scroll),
    m_horizontal_scroll(other.m_horizontal_scroll),_scale(other._scale),_curr_color(other._curr_color)
{
}

FiguresManager::~FiguresManager()
{
}

FiguresManager& FiguresManager::operator =(const FiguresManager& other)
{
    m_id = other.m_id;
    m_tool = other.m_tool;
    m_temp_figure = NULL;
    m_figures = other.m_figures;
    m_new_selection = other.m_new_selection;
    m_vertical_scroll = other.m_vertical_scroll;
    m_horizontal_scroll = other.m_horizontal_scroll;
    _scale = other._scale;
    _curr_color = other._curr_color;
    return (*this);
}

void FiguresManager::setScroll(QScrollBar *horizontal, QScrollBar *vertical,const QSize &size)
{
    m_horizontal_scroll = horizontal;
    m_vertical_scroll = vertical;
    m_viewport_size = size;
}

void FiguresManager::setScalePointer(uint *scale)
{
    _scale = scale;
}

ShapeBase* FiguresManager::value(qint64 id) const
{
    return m_figures.value(id);
}

qint64 FiguresManager::addValue(ShapeBase *value)
{
    value->setID(++m_id);
    const qint64 tmp = m_figures.insert(m_id,value).key();
    qDebug() << "tmp" << tmp;
    qDebug() << "tmp == (m_id - 1)" << (tmp == (m_id - 1));
    return (tmp == (m_id)) ? tmp : -1;
}

ShapeBase *FiguresManager::takeAt(qint64 id)
{
    return m_figures.take(id);

}

bool FiguresManager::removeAt(qint64 id)
{
    return m_figures.remove(id) == m_data.remove(id);
}

void FiguresManager::setEvidenceKey(const QString& key)
{
    _ev_key = key;
}

QString FiguresManager::stringById(qint64 id)
{
    QString retVal;
    if(m_data.contains(id))
    {
        retVal = m_data.value(id);
    }
    return retVal;
}

void FiguresManager::clear()
{
    m_id = -1;
    m_tool = NoTool;
    m_prev_cursor = QPoint();
    if(m_temp_figure != NULL)
        m_temp_figure->deleteLater();
    m_temp_figure = NULL;
    m_figures.clear();
}

void FiguresManager::setTool(Tool tool)
{
    m_new_selection = true;
    qDebug() << "tool" << tool;
    m_tool = tool;
    if(m_temp_figure != NULL)
        m_temp_figure->deleteLater();
    switch (tool) {
    case ArrowTool:
        m_temp_figure = new Arrow(this);
        break;
    case EllipseTool:
        m_temp_figure = new Ellipse(this);
        break;
    case PolygonTool:
        m_temp_figure = new Polygon(this);
        break;
    case RectTool:
        m_temp_figure = new Rect(this);
        break;
    default:
        m_temp_figure = NULL;
        return;
    }
}

void FiguresManager::setCurrentColor(uint* currentColor)
{
    _curr_color = currentColor;
}

void FiguresManager::setCurrentParams(qint64 evidenceID, qint64 entryID, qint64 diagnosisID, uint color, Tool tool)
{
    m_tool = tool;
    if(m_temp_figure != NULL)
        m_temp_figure->deleteLater();
    switch (tool) {
    case ArrowTool:
        m_temp_figure = new Arrow(this);
        break;
    case EllipseTool:
        m_temp_figure = new Ellipse(this);
        break;
    case PolygonTool:
        m_temp_figure = new Polygon(this);
        break;
    case RectTool:
        m_temp_figure = new Rect(this);
        break;
    default:
        m_temp_figure = NULL;
        return;
    }
    m_temp_figure->setColor(color);
    m_temp_figure->setEntryID(evidenceID);
    m_temp_figure->setEntryID(entryID);
    m_temp_figure->setDiagnosisID(diagnosisID);
}

void FiguresManager::drawer(QWidget *widget)
{
    QPainter painter(widget);
    QPen pen;
//    qDebug() << "draw" << "tool" << m_tool;
    if (NoTool != m_tool) {
        pen.setStyle(Qt::DashLine);

        if(m_temp_figure != NULL)
        {
            m_temp_figure->setEvidenceKey(_ev_key);
            m_temp_figure->setColor(*_curr_color);
            //        m_temp_figure->setWidth(2);
            if(ArrowTool == m_tool && m_temp_figure->getFigureType() == FigureType::ArrowFigure) {
                Arrow* arrow_obj = qobject_cast<Arrow*>(m_temp_figure);
                drawArrow(&painter,&pen, arrow_obj);
            } else if(EllipseTool == m_tool && m_temp_figure->getFigureType() == FigureType::EllipseFigure) {
                Ellipse* ellipse_obj = qobject_cast<Ellipse* >(m_temp_figure);
                drawEllipse(&painter,&pen,ellipse_obj);
            } else if(PolygonTool == m_tool && m_temp_figure->getFigureType() == FigureType::PolygonFigure) {
                Polygon* polygon_obj = qobject_cast<Polygon* >(m_temp_figure);
                drawPolygon(&painter,&pen,polygon_obj);
            } else if(RectTool == m_tool && m_temp_figure->getFigureType() == FigureType::RectFigure) {
                Rect* rect_obj = qobject_cast<Rect* >(m_temp_figure);
                drawRect(&painter,&pen,rect_obj);
            }
        }
    }
    drawFigures(widget);
}

void FiguresManager::mousePress(QWidget *widget, QMouseEvent *event)
{
    _x = m_horizontal_scroll->value();
    _y = m_vertical_scroll->value();
    bool reDraw = true;
    Polygon* pol;
    QPolygon poly;

    qreal scale =  (*_scale);
    qDebug() << "scale" <<scale;

//    qDEbug() << "sadas" << m_temp_figure == NULL;

    m_prev_cursor = (event->pos() + QPoint(_x,_y) ) / scale;

    if(m_new_selection && event->buttons() & Qt::LeftButton)
    {
        switch (m_tool) {
        case ArrowTool:
            if(m_temp_figure == NULL)
                m_temp_figure = new Arrow(this);
            else if(m_temp_figure->clearFigure() != FigureType::ArrowFigure)
            {
                m_temp_figure->deleteLater();
                m_temp_figure = new Arrow(this);
            }
            break;
        case EllipseTool:
            if(m_temp_figure == NULL)
                m_temp_figure = new Ellipse(this);
            else if(m_temp_figure->clearFigure() != FigureType::EllipseFigure)
            {
                m_temp_figure->deleteLater();
                m_temp_figure = new Ellipse(this);
            }
            break;
        case PolygonTool:
            qDebug() << "pol count";
            if(m_temp_figure == NULL)
            {
                m_temp_figure = new Polygon(this);
            }
            pol = qobject_cast<Polygon*>(m_temp_figure);
            pol->setCoordinates(pol->getCoordinates() << m_prev_cursor << m_prev_cursor);
            qDebug() << "pol count"<< pol->getCoordinates().count();
            break;
        case RectTool:
            if(m_temp_figure == NULL)
                m_temp_figure = new Rect(this);
            else if(m_temp_figure->clearFigure() != FigureType::RectFigure)
            {
                m_temp_figure->deleteLater();
                m_temp_figure = new Rect(this);
                qDebug() << "rect" << m_temp_figure;
            }
            break;
        default:
            if(m_temp_figure != NULL)
            {
                m_temp_figure->deleteLater();
                m_temp_figure = NULL;
            }
            reDraw = false;
            break;
        }
        if(reDraw)
            widget->repaint();
    }
}

void FiguresManager::mouseMove(QWidget *widget, QMouseEvent *event)
{
    _x = m_horizontal_scroll->value();
    _y = m_vertical_scroll->value();
    qreal scale = (*_scale);
    QPoint pos = (event->pos() + QPoint(_x,_y)) / scale ;
    bool reDraw = true;
    if(m_new_selection && event->buttons() && Qt::LeftButton)
    {
        Arrow* arr;
        Ellipse* ell;
        Polygon* pol;
        Rect* rec;
        QPolygon tmp;
        switch (m_tool) {
        case ArrowTool:
            arr = qobject_cast<Arrow*>(m_temp_figure);
            arr->setCoordinates(m_prev_cursor,pos);
            break;
        case EllipseTool:
            ell = qobject_cast<Ellipse*>(m_temp_figure);
            ell->setCoordinates(m_prev_cursor,pos);
            break;
        case Tool::PolygonTool:
            pol = qobject_cast<Polygon*>(m_temp_figure);
            tmp = pol->getCoordinates();
            if(tmp.count()) tmp.setPoint(tmp.count() - 1, pos);
            pol->setCoordinates(tmp);
            break;
        case RectTool:
            rec = qobject_cast<Rect*>(m_temp_figure);
            rec->setCoordinates(m_prev_cursor,pos);
            break;
        case NoTool:
            reDraw = false;
            break;
        }
    } else ///??? mb NOT working
        reDraw = false;
    /* когда изображение слишком большое(необходима прокрутка) */
    if(event->buttons() & Qt::MiddleButton &&
       (m_viewport_size.height() < m_viewport_size.height() ||
        m_viewport_size.width() < widget->size().width()))
    {
        QPoint globPos = widget->mapToGlobal(pos);
        QPoint prev = widget->mapToGlobal(m_prev_cursor);
        int horValue = m_horizontal_scroll->value();
//        scroll_area_->horizontalScrollBar()
        int verValue = m_vertical_scroll->value();


        QPoint delta = globPos - prev;
        m_prev_cursor = pos;

        horValue += delta.x();
        verValue += delta.y();

        m_horizontal_scroll->setValue(horValue);
        m_vertical_scroll->setValue(verValue);
    }
    if(reDraw)
        widget->repaint();
}

void FiguresManager::mouseRelease()
{
    m_last_tool = m_tool;
}

qint64 FiguresManager::confirm()
{
    qint64 result = -1;
    if(m_temp_figure == NULL) return result;
    if(!m_temp_figure->hasDefaultCoordinates())
    {
        qint64 tmpId = addValue(m_temp_figure);
        qDebug() << "tmpId" << tmpId;
        bool ok = 0 <= tmpId;
        qDebug() << "res" << result;
        if(ok)
        {
            ok = (tmpId == m_data.insert(tmpId,m_temp_figure->getStrData()).key());
            m_temp_figure = NULL;
            m_tool = NoTool;
            result = ok ? tmpId: -1;
        }
    }
    return result;
}


void FiguresManager::calcDx(int newVal)
{
    _dx = _x - newVal;
    qDebug() << "_dx" << _dx;
}

void FiguresManager::calcDy(int newVal)
{
    _dy = _y - newVal;
    qDebug() << "_dy" << _dy;
}

void FiguresManager::drawArrow(QPainter *painter,QPen *pen, Arrow *arrowObj)
{
    if(arrowObj == NULL)
    {
        qDebug() << arrowObj << "arrow_obj is null!";
        return;
    }

    qreal scale = (*_scale);

    pen->setWidth(arrowObj->getWidth());
    pen->setColor(QColor(arrowObj->getColor()));
    painter->setPen(*pen);
    QLineF line = arrowObj->getCoordinates();
    qDebug() << "line1" << line;
    QPointF p1 = line.p1() * scale;
    QPointF p2 = line.p2() * scale;


    qDebug() << "line2" << line;
    qDebug() << "line3" << line << QPointF(_dx,_dy);

    line.setP1(p1);
    line.setP2(p2);

    if(1 < line.length()) {
        qreal angle = ::acos(line.dx() / line.length());
        qreal Pi = atan(1)*4;
        if(0 <= line.dy())
            angle = (Pi*2 - angle);
        qreal arrowScale = arrowObj->getArrowScale();
        QPointF arrowP1 = line.p1() + QPointF(sin(angle + Pi / 3) * (arrowScale ),
                                              cos(angle + Pi / 3) * (arrowScale ));
        QPointF arrowP2 = line.p1() + QPointF(sin(angle + Pi - Pi / 3) * (arrowScale),
                                              cos(angle + Pi - Pi / 3) * (arrowScale ));
        QPolygonF arrowTop;
        arrowTop << line.p1() + QPointF(_dx,_dy) << arrowP1 + QPointF(_dx,_dy) << arrowP2 + QPointF(_dx,_dy);

        p1 +=  QPointF(_dx,_dy);
        p2 +=  QPointF(_dx,_dy);
        line.setP1(p1);
        line.setP2(p2);
        painter->drawLine(line);
        painter->drawPolygon(arrowTop);
        QLineF newLine(line.p1()/scale,line.p2()/scale);
        arrowObj->setCoordinates(newLine);
    }
}

void FiguresManager::drawEllipse(QPainter *painter,QPen* pen, Ellipse *ellipseObj)
{
    if(ellipseObj == NULL)
    {
        qDebug() << ellipseObj << "ellipse_obj is null!";
        return;
    }
    qreal scale = (*_scale);
    pen->setWidth(ellipseObj->getWidth());
    pen->setColor(QColor(ellipseObj->getColor()));
    painter->setPen(*pen);
    QRect elli = ellipseObj->getCoordinates();
    QPoint ellTopLeft = elli.topLeft() * scale + QPoint(_dx,_dy);
    QPoint ellBottomRight = elli.bottomRight() * scale + QPoint(_dx,_dy);

    elli.setTopLeft(ellTopLeft);
    elli.setBottomRight(ellBottomRight);

    if(1 < elli.height() && 1 < elli.width())
    {
        painter->drawEllipse(elli);
    }
    QRect newRect(ellTopLeft/scale,ellBottomRight/scale);
    ellipseObj->setCoordinates(newRect);
    _x = m_horizontal_scroll->value();
    _y = m_vertical_scroll->value();
}

void FiguresManager::drawPolygon(QPainter *painter,QPen *pen, Polygon *polygonObj)
{
    QPoint point;
    qreal scale = (*_scale);
    if(polygonObj == NULL)
    {
        qDebug() << polygonObj << "polygon_obj is null!";
        return;
    }
    pen->setWidth(polygonObj->getWidth());
    pen->setColor(QColor(polygonObj->getColor()));
    painter->setPen(*pen);
    QPolygon pol = polygonObj->getCoordinates();
    for(int i = 0; i< pol.size(); ++i)
    {
        point.setX(pol[i].x());
        point.setY(pol[i].y());
        point = point * scale + QPoint(_dx,_dy);
        pol.remove(i);
        pol.insert(i,point);
    }
    painter->drawPolygon(pol);
    QPolygon newPol;
    for(int i = 0; i< pol.size(); ++i)
    {
        newPol << pol.at(i)/scale;
    }
    polygonObj->setCoordinates(newPol);
    _x = m_horizontal_scroll->value();
    _y = m_vertical_scroll->value();

}

void FiguresManager::drawRect(QPainter *painter,QPen *pen, Rect *rectObj)
{
    if(rectObj == NULL)
    {
        qDebug() << rectObj << "rect_obj is null!";
        return;
    }
    qreal scale = (*_scale);
    pen->setWidth(rectObj->getWidth());
    pen->setColor(QColor(rectObj->getColor()));
    painter->setPen(*pen);
    QRect rec = rectObj->getCoordinates();
    QPoint recTopLeft = rec.topLeft() * scale  + QPoint(_dx,_dy);
    QPoint recBottomRight = rec.bottomRight() * scale  + QPoint(_dx,_dy);
    rec.setTopLeft(recTopLeft);
    rec.setBottomRight(recBottomRight);
    painter->drawRect(rec);
    qDebug() << "rec" << rec;
    QRect newRect(recTopLeft/scale,recBottomRight/scale);
    rectObj->setCoordinates(newRect);
    _x = m_horizontal_scroll->value();
    _y = m_vertical_scroll->value();
}

void FiguresManager::drawFigures(QWidget* widget)
{
    QPainter painter(widget);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    for(auto it = m_figures.begin(); it != m_figures.end(); ++it)
    {
        ShapeBase* shape = it.value();
        if(shape == NULL)
        {
            continue;
        }
        pen.setColor(QColor(shape->getColor()));
        pen.setWidth(shape->getWidth());
        switch (shape->getFigureType()) {
        case FigureType::ArrowFigure:

            drawArrow(&painter,&pen,qobject_cast<Arrow*>(shape));
            break;
        case FigureType::EllipseFigure:
            drawEllipse(&painter,&pen,qobject_cast<Ellipse* >(shape));
            break;
        case FigureType::PolygonFigure:
            drawPolygon(&painter,&pen,qobject_cast<Polygon* >(shape));
            break;
        case FigureType::RectFigure:
            drawRect(&painter,&pen,qobject_cast<Rect* >(shape));
            break;
        default:
            break;
        }
    }
}

qint64 FiguresManager::getDbLastMarkID()
{
    qint64 tmp = -1;
    if(!m_db.isOpen())
    {
        qDebug() << tr("cannot db connection: %1").arg(m_db.lastError().text());
    }
    QSqlQuery q;
    q.exec("SELECT LAST_INSERT_ID();");
    if(q.next())
    {
        bool ok = true;
        tmp = q.value(0).toInt(&ok);
        tmp = ok ? tmp : -1;
    }
    else
    {
        qDebug() << "FiguresManager::getDbLastMarkID()" << q.lastError().text();
    }
    return tmp;
}

}
