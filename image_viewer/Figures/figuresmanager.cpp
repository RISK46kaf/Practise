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
#include "Tables/defaultnames.h"

namespace Figures {


FiguresManager::FiguresManager(QObject *parent) : QObject(parent),
    m_id(-1),m_tool(Tool::NoTool), m_temp_figure(NULL), m_new_selection(0), m_scroll_area(NULL)
{
}

FiguresManager::FiguresManager(const FiguresManager &other) : QObject(0),
    m_id(other.m_id), m_tool(other.m_tool), m_temp_figure(NULL), m_figures(other.m_figures),
    m_new_selection(other.m_new_selection), m_scroll_area(other.m_scroll_area)
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
    m_scroll_area = other.m_scroll_area;
    return (*this);
}

void FiguresManager::setScrollArea(const QScrollArea *scrollArea)
{
    m_scroll_area = scrollArea;
}

ShapeBase* FiguresManager::value(qint64 id) const
{
    return m_figures.value(id);
}

qint64 FiguresManager::addValue(ShapeBase *value)
{
    value->setID(++m_id);

    const qint64 tmp = m_figures.insert(m_id,value).key();
    return tmp == m_id ? tmp : -1;
}

void FiguresManager::clear()
{
    m_id = -1;
    m_tool = NoTool;
    m_prev_cursor = QPoint();
    if(m_temp_figure != NULL)
        m_temp_figure->deleteLater();
    m_figures.clear();
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

void FiguresManager::drawer(QPainter *painter, QPen *pen, qreal scale) const
{
    if (NoTool != m_tool) {
        pen->setStyle(Qt::DashLine);

        if(m_temp_figure == NULL)
        {
            qDebug() << m_temp_figure << "m_temp_figure is null!";
            return;
        }
//        m_temp_figure->setColor(0xFFFFFFFF);
//        m_temp_figure->setWidth(2);
        if(ArrowTool == m_tool && m_temp_figure->getFigureType() == FigureType::ArrowFigure) {
            Arrow* arrow_obj = qobject_cast<Arrow*>(m_temp_figure);
            drawArrow(painter,pen, arrow_obj,scale);
        } else if(EllipseTool == m_tool && m_temp_figure->getFigureType() == FigureType::EllipseFigure) {
            Ellipse* ellipse_obj = qobject_cast<Ellipse* >(m_temp_figure);
            drawEllipse(painter,pen,ellipse_obj,scale);
        } else if(PolygonTool == m_tool && m_temp_figure->getFigureType() == FigureType::PolygonFigure) {
            Polygon* polygon_obj = qobject_cast<Polygon* >(m_temp_figure);
            drawPolygon(painter,pen,polygon_obj,scale);
        } else if(RectTool == m_tool && m_temp_figure->getFigureType() == FigureType::RectFigure) {
            Rect* rect_obj = qobject_cast<Rect* >(m_temp_figure);
            drawRect(painter,pen,rect_obj,scale);
        }
    }
    this->drawFigures(painter, pen, scale);
}

void FiguresManager::musePress(QWidget *widget, QMouseEvent *event, qreal scale)
{
    bool nothingDraw = false;

    m_prev_cursor = event->pos() / scale;

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
            if(m_temp_figure == NULL)
                m_temp_figure = new Polygon(this);
            else if(m_temp_figure->clearFigure() != FigureType::PolygonFigure)
            {
                m_temp_figure->deleteLater();
                Polygon* pol = new Polygon(this);
                pol->setCoordinates(pol->getCoordinates() << m_prev_cursor << m_prev_cursor);
                m_temp_figure = pol;
            }
            break;
        case RectTool:
            if(m_temp_figure == NULL)
                m_temp_figure = new Rect(this);
            else if(m_temp_figure->clearFigure() != FigureType::RectFigure)
            {
                m_temp_figure->deleteLater();
                m_temp_figure = new Rect(this);
            }
            break;
        default:
            if(m_temp_figure != NULL)
            {
                m_temp_figure->deleteLater();
                m_temp_figure = NULL;
            }
            nothingDraw = true;
            break;
        }
        if(!nothingDraw)
            widget->update();
    }
}

void FiguresManager::mouseMove(QWidget *widget, QMouseEvent *event, qreal scale)
{
    QPoint pos = event->pos() / scale;
    bool nothingDraw = false;
    /*some fix
    if (event->pos().x() < 0)
        pos.setX(0);

    if (width() < event->pos().x())
        pos.setX(widget->width() - 1);

    if (anEvent->pos().y() < 0)
        pos.setY(0);

    if (height() < anEvent->pos().y())
        pos.setY(widget->height() - 1);*/
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
            tmp.setPoint(tmp.count() - 1, pos);
            pol->setCoordinates(tmp);
            break;
        case RectTool:
            rec = qobject_cast<Rect*>(m_temp_figure);
            rec->setCoordinates(m_prev_cursor,pos);
            break;
        case NoTool:
            nothingDraw = true;
            break;
        }
    } else ///??? mb NOT working
        nothingDraw = true;
    /* когда изображение слишком большое(необходима прокрутка) */
    if(event->buttons() & Qt::MiddleButton &&
       (m_scroll_area->size().height() < widget->size().height() ||
        m_scroll_area->size().width() < widget->size().width()))
    {
        QPoint globPos = widget->mapToGlobal(pos);
        QPoint prev = widget->mapToGlobal(m_prev_cursor);
        int horValue = m_scroll_area->horizontalScrollBar()->value();
//        scroll_area_->horizontalScrollBar()
        int verValue = m_scroll_area->verticalScrollBar()->value();


        QPoint delta = globPos - prev;
        m_prev_cursor = pos;

        horValue += delta.x();
        verValue += delta.y();

        m_scroll_area->horizontalScrollBar()->setValue(horValue);
        m_scroll_area->verticalScrollBar()->setValue(verValue);
    }
    if(!nothingDraw)
        widget->update();
}

void FiguresManager::insertData(QSqlDatabase& db,
                                QString& host,
                                QString& user,
                                QByteArray& pass)
{
    if(!db.isOpen())
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(host);
        db.setUserName(user);
        db.setPassword(decodePass(pass));
        if(!db.open())
        {
            qDebug() << tr("conection error: ").arg(db.lastError());
            return;
        } else if(!db.isOpen())
        {
            qDebug() << tr("conection error: ").arg(db.lastError());
            return;
        }
    }
    /// do smth

}

void FiguresManager::drawArrow(QPainter *painter,QPen *pen, Arrow *arrowObj, qreal scale) const
{
    if(arrowObj == NULL)
    {
        qDebug() << arrowObj << "arrow_obj is null!";
        return;
    }
    pen->setWidth(arrowObj->getWidth());
    pen->setColor(QColor(arrowObj->getColor()));
    painter->setPen(*pen);
    QLineF line = arrowObj->getCoordinates();
    QPointF p1 = line.p1() * scale;
    QPointF p2 = line.p2() * scale;

    line.setP1(p1);
    line.setP2(p2);

    if(1 < line.length()) {
        qreal angle = ::acos(line.dx() / line.length());
        qreal Pi = atan(1)*4;
        if(0 <= line.dy())
            angle = (Pi*2 - angle);
        qreal arrowScale = arrowObj->getArrowScale();
        QPointF arrowP1 = line.p1() + QPointF(sin(angle + Pi / 3) * arrowScale * scale,
                                              cos(angle + Pi / 3) * arrowScale * scale);
        QPointF arrowP2 = line.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowScale * scale,
                                              cos(angle + Pi - Pi / 3) * arrowScale * scale);
        QPolygonF arrowTop;
        arrowTop << line.p1() << arrowP1 << arrowP2;
        painter->drawLine(line);
        painter->drawPolygon(arrowTop);
    }
}

void FiguresManager::drawEllipse(QPainter *painter,QPen* pen, Ellipse *ellipseObj, qreal scale) const
{
    if(ellipseObj == NULL)
    {
        qDebug() << ellipseObj << "ellipse_obj is null!";
        return;
    }
    pen->setWidth(ellipseObj->getWidth());
    pen->setColor(ellipseObj->getColor());
    painter->setPen(*pen);
    QRect elli = ellipseObj->getCoordinates();
    QPoint ellTopLeft = elli.topLeft() * scale;
    QPoint ellBottomRight = elli.bottomRight() * scale;

    elli.setTopLeft(ellTopLeft);
    elli.setBottomRight(ellBottomRight);

    if(1 < elli.height() && 1 < elli.width())
    {
        painter->drawEllipse(elli);
    }
}

void FiguresManager::drawPolygon(QPainter *painter,QPen *pen, Polygon *polygonObj, qreal scale) const
{
    QPoint point;
    if(polygonObj == NULL)
    {
        qDebug() << polygonObj << "polygon_obj is null!";
        return;
    }
    pen->setWidth(polygonObj->getWidth());
    pen->setColor(polygonObj->getColor());
    painter->setPen(*pen);
    QPolygon pol = polygonObj->getCoordinates();
    for(int i = 0; i< pol.size(); ++i)
    {
        point.setX(pol[i].x());
        point.setY(pol[i].y());
        point *= scale;
        pol.remove(i);
        pol.insert(i,point);
    }
    painter->drawPolygon(pol);
}

void FiguresManager::drawRect(QPainter *painter,QPen *pen, Rect *rectObj, qreal scale) const
{
    if(rectObj == NULL)
    {
        qDebug() << rectObj << "rect_obj is null!";
        return;
    }
    pen->setWidth(rectObj->getWidth());
    pen->setColor(rectObj->getColor());
    painter->setPen(*pen);
    QRect rec = rectObj->getCoordinates();
    QPoint recTopLeft = rec.topLeft() * scale;
    QPoint recBottomRight = rec.bottomRight() * scale;
    rec.setTopLeft(recTopLeft);
    rec.setBottomRight(recBottomRight);
    painter->drawRect(rec);
}

void FiguresManager::drawFigures(QPainter *painter, QPen *pen, qreal scale) const
{
    for(auto it = m_figures.begin(); it != m_figures.end(); ++it)
    {
        ShapeBase* shape = it.value();
        if(shape == NULL)
        {
            continue;
        }
        pen->setColor(QColor(shape->getColor()));
        pen->setWidth(shape->getWidth());
        pen->setStyle(Qt::SolidLine);
        painter->setPen(*pen);
        switch (shape->getFigureType()) {
        case FigureType::ArrowFigure:

            drawArrow(painter,pen,qobject_cast<Arrow*>(m_temp_figure),scale);
            break;
        case FigureType::EllipseFigure:
            drawEllipse(painter,pen,qobject_cast<Ellipse* >(m_temp_figure),scale);
            break;
        case FigureType::PolygonFigure:
            drawPolygon(painter,pen,qobject_cast<Polygon* >(m_temp_figure),scale);
            break;
        case FigureType::RectFigure:
            drawRect(painter,pen,qobject_cast<Rect* >(m_temp_figure),scale);
            break;
        default:
            break;
        }
    }
}



}
