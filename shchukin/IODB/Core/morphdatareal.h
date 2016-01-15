#ifndef MORPHDATACORRELATION_H
#define MORPHDATACORRELATION_H
#include <QtCore>
#include "morphdata.h"

namespace Core {

struct MorphDataReal
{
    qreal Spots;
    qreal SpotsSquare;
    qreal ExtCircuit8Len;
    qreal ExtCircuit4Len;
    qreal ExtPerimetr;
    qreal IntCircuit8Len;
    qreal IntCircuit4Len;
    qreal IntPerimetr;
    qreal Square;
    qreal  Fullness;
    qreal  ShapeFactor;
    qreal  MarkId; /// id макрера к кот относятся
    // Фере
    qreal MinDiametr;
    qreal AngleMin;
    qreal MaxDiametr;
    qreal AngleMax;
    qreal AverageDiametr;
    qreal MeanSquareDiametr;
//    bool FerValid;
    // Радиус
    qreal MaxRadius;
    qreal MinRadius;
    qreal AverageRadius;
    qreal MeanSquareRadius;
    qreal InertiaMoment;
    qreal RelInertiaMoment;

    MorphDataReal();

    MorphDataReal& operator=(const MorphDataReal& other);
    MorphDataReal& operator=(const MorphData& other);
    MorphDataReal& operator/=(const MorphDataReal& other);
    MorphDataReal& operator/=(const MorphData& other);
    MorphDataReal& operator/=(qint64 num);
    MorphDataReal& operator+=(const MorphData& other);
    MorphDataReal& operator+=(const MorphDataReal& other);
    MorphDataReal& operator-=(const MorphData& other);
    MorphDataReal& operator-=(const MorphDataReal& other);
    MorphDataReal& operator*=(const MorphDataReal& other);

    MorphDataReal operator+(const MorphDataReal& other);
    MorphDataReal operator-(const MorphDataReal& other);
    MorphDataReal operator*(const MorphDataReal& other);
    MorphDataReal operator/(const MorphDataReal& other);
    MorphDataReal operator/(qint64 num);

    static MorphDataReal mophSqrt(const MorphDataReal& other);

};

}
#endif // MORPHDATACORRELATION_H
