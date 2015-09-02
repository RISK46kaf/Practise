#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);

signals:

public slots:
    void setImage(QImage& i);
private:
    QImage img;
protected:
    void paintEvent(QPaintEvent *evt);
};

#endif // VIEW_H
