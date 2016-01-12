#ifndef MORPHDATA_H
#define MORPHDATA_H
#include <QtCore>

struct MorphData
{
    qint64 Spots;
    qint64 SpotsSquare;
    qint64 ExtCircuit8Len;
    qint64 ExtCircuit4Len;
    qint64 ExtPerimetr;
    qint64 IntCircuit8Len;
    qint64 IntCircuit4Len;
    qint64 IntPerimetr;
    qint64 Square;
    qreal  Fullness;
    qreal  ShapeFactor;
    qreal  MarkId; /// id макрера к кот относятся
    // Фере
    qreal MinDiametr;
    qint64 AngleMin;
    qreal MaxDiametr;
    qint64 AngleMax;
    qreal AverageDiametr;
    qreal MeanSquareDiametr;
    bool FerValid;
    // Радиус
    qreal MaxRadius;
    qreal MinRadius;
    qreal AverageRadius;
    qreal MeanSquareRadius;
    QPoint MaxRadiusPoint;
    QPoint MinRadiusPoint;
    qreal InertiaMoment;
    qreal RelInertiaMoment;
    bool RadValid;
};
#endif // MORPHDATA_H
