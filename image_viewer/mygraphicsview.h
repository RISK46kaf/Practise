#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QResizeEvent>
#include <QObject>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView();

signals:
    void resized();
    void changed();
    void scrolled();
public slots:
    void scrollEvent();
protected:
    void resizeEvent(QResizeEvent *event);


};

#endif // MYGRAPHICSVIEW_H
