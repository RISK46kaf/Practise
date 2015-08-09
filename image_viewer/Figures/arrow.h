#ifndef ARROW_H
#define ARROW_H

class ShapeBase;

class Arrow: public ShapeBase
{
public:
    Arrow();
    explicit Arrow(QLineF coordinates);
    Arrow(QLineF coordinates, uint color);

    QLineF getCoordinates() const;

    void setCoordinates(const QLineF& coordinates);
    void setCoordinates(const QPointF &pt1, const QPointF &pt2);
    void setCoordinates(qreal x1, qreal y1, qreal x2, qreal y2);
    void setCoordinates(const QLine &line);
private:
    QLineF m_coordinates;

private:
    void setStrData();
};

#endif // ARROW_H
