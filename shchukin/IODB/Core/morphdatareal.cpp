#include "morphdatareal.h"

using namespace Core;

MorphDataReal::MorphDataReal()
{
    Spots = 0;
    SpotsSquare = 0;
    ExtCircuit8Len = 0;
    ExtCircuit4Len = 0;
    ExtPerimetr = 0;
    IntCircuit8Len = 0;
    IntCircuit4Len = 0;
    IntPerimetr = 0;
    Square = 0;
    Fullness = 0;
    ShapeFactor = 0;
    MarkId = -1;
    // Фере
    MinDiametr = 0;
    AngleMin = 0;
    MaxDiametr = 0;
    AngleMax = 0;
    AverageDiametr = 0;
    MeanSquareDiametr = 0;
    // Радиус
    MaxRadius = 0;
    MinRadius = 0;
    AverageRadius = 0;
    MeanSquareRadius = 0;
    InertiaMoment = 0;
    RelInertiaMoment = 0;
}

MorphDataReal &MorphDataReal::operator=(const MorphDataReal &other)
{
    Spots = qAbs(other.Spots);
    SpotsSquare = qAbs(other.SpotsSquare);
    ExtCircuit8Len = qAbs(other.ExtCircuit8Len);
    ExtCircuit4Len = qAbs(other.ExtCircuit4Len);
    ExtPerimetr = qAbs(other.ExtPerimetr);
    IntCircuit8Len = qAbs(other.IntCircuit8Len);
    IntCircuit4Len = qAbs(other.IntCircuit4Len);
    IntPerimetr = qAbs(other.IntPerimetr);
    Square = qAbs(other.Square);
    Fullness = qAbs(other.Fullness);
    ShapeFactor = qAbs(other.ShapeFactor);
    MarkId = qAbs(other.MarkId);
    // Фере
    MinDiametr = qAbs(other.MinDiametr);
    AngleMin = qAbs(other.AngleMin);
    MaxDiametr = qAbs(other.MaxDiametr);
    AngleMax = qAbs(other.AngleMax);
    AverageDiametr = qAbs(other.AverageDiametr);
    MeanSquareDiametr = qAbs(other.MeanSquareDiametr);
    // Радиус
    MaxRadius = qAbs(other.MaxRadius);
    MinRadius = qAbs(other.MinRadius);
    AverageRadius = qAbs(other.AverageRadius);
    MeanSquareRadius = qAbs(other.MeanSquareRadius);
    InertiaMoment = qAbs(other.InertiaMoment);
    RelInertiaMoment = qAbs(other.RelInertiaMoment);
    return (*this);
}

MorphDataReal &MorphDataReal::operator=(const MorphData &other)
{
    Spots = other.Spots;
    SpotsSquare = other.SpotsSquare;
    ExtCircuit8Len = other.ExtCircuit8Len;
    ExtCircuit4Len = other.ExtCircuit4Len;
    ExtPerimetr = other.ExtPerimetr;
    IntCircuit8Len = other.IntCircuit8Len;
    IntCircuit4Len = other.IntCircuit4Len;
    IntPerimetr = other.IntPerimetr;
    Square = other.Square;
    Fullness = other.Fullness;
    ShapeFactor = other.ShapeFactor;
    MarkId = -1;
    // Фере
    MinDiametr = other.MinDiametr;
    AngleMin = other.AngleMin;
    MaxDiametr = other.MaxDiametr;
    AngleMax = other.AngleMax;
    AverageDiametr = other.AverageDiametr;
    MeanSquareDiametr = other.MeanSquareDiametr;
    // Радиус
    MaxRadius = other.MaxRadius;
    MinRadius = other.MinRadius;
    AverageRadius = other.AverageRadius;
    MeanSquareRadius = other.MeanSquareRadius;
    InertiaMoment = other.InertiaMoment;
    RelInertiaMoment = other.RelInertiaMoment;
    return (*this);
}


MorphDataReal &MorphDataReal::operator/=(const MorphData &other)
{
    Spots /= other.Spots;
    SpotsSquare /= other.SpotsSquare;
    ExtCircuit8Len /= other.ExtCircuit8Len;
    ExtCircuit4Len /= other.ExtCircuit4Len;
    ExtPerimetr /= other.ExtPerimetr;
    IntCircuit8Len /= other.IntCircuit8Len;
    IntCircuit4Len /= other.IntCircuit4Len;
    IntPerimetr /= other.IntPerimetr;
    Square /= other.Square;
    Fullness /= other.Fullness;
    ShapeFactor /= other.ShapeFactor;
    MarkId = -1;
    // Фере
    MinDiametr /= other.MinDiametr;
    AngleMin /= other.AngleMin;
    MaxDiametr /= other.MaxDiametr;
    AngleMax /= other.AngleMax;
    AverageDiametr /= other.AverageDiametr;
    MeanSquareDiametr /= other.MeanSquareDiametr;
    // Радиус
    MaxRadius /= other.MaxRadius;
    MinRadius /= other.MinRadius;
    AverageRadius /= other.AverageRadius;
    MeanSquareRadius /= other.MeanSquareRadius;
    InertiaMoment /= other.InertiaMoment;
    RelInertiaMoment /= other.RelInertiaMoment;
    return (*this);
}

MorphDataReal &MorphDataReal::operator/=(qint64 num)
{
    Spots /= num;
    SpotsSquare /= num;
    ExtCircuit8Len /= num;
    ExtCircuit4Len /= num;
    ExtPerimetr /= num;
    IntCircuit8Len /= num;
    IntCircuit4Len /= num;
    IntPerimetr /= num;
    Square /= num;
    Fullness /= num;
    ShapeFactor /= num;
    MarkId = -1;
    // Фере
    MinDiametr /= num;
    AngleMin /= num;
    MaxDiametr /= num;
    AngleMax /= num;
    AverageDiametr /= num;
    MeanSquareDiametr /= num;
    // Радиус
    MaxRadius /= num;
    MinRadius /= num;
    AverageRadius /= num;
    MeanSquareRadius /= num;
    InertiaMoment /= num;
    RelInertiaMoment /= num;
    return (*this);
}

MorphDataReal MorphDataReal::operator+(const MorphDataReal& other)
{
    MorphDataReal retVal = (*this);
    retVal += other;
    return retVal;
}

MorphDataReal MorphDataReal::operator-(const MorphDataReal &other)
{
    MorphDataReal retVal = (*this);
    retVal -= other;
    return retVal;
}

MorphDataReal &MorphDataReal::operator+=(const MorphDataReal &other)
{
    Spots += other.Spots;
    SpotsSquare += other.SpotsSquare;
    ExtCircuit8Len += other.ExtCircuit8Len;
    ExtCircuit4Len += other.ExtCircuit4Len;
    ExtPerimetr += other.ExtPerimetr;
    IntCircuit8Len += other.IntCircuit8Len;
    IntCircuit4Len += other.IntCircuit4Len;
    IntPerimetr += other.IntPerimetr;
    Square += other.Square;
    Fullness += other.Fullness;
    ShapeFactor += other.ShapeFactor;
    MarkId = -1;
    // Фере
    MinDiametr += other.MinDiametr;
    AngleMin += other.AngleMin;
    MaxDiametr += other.MaxDiametr;
    AngleMax += other.AngleMax;
    AverageDiametr += other.AverageDiametr;
    MeanSquareDiametr += other.MeanSquareDiametr;
    // Радиус
    MaxRadius += other.MaxRadius;
    MinRadius += other.MinRadius;
    AverageRadius += other.AverageRadius;
    MeanSquareRadius += other.MeanSquareRadius;
    InertiaMoment += other.InertiaMoment;
    RelInertiaMoment += other.RelInertiaMoment;
    return (*this);
}

MorphDataReal &MorphDataReal::operator-=(const MorphData &other)
{
    Spots -= other.Spots;
    SpotsSquare -= other.SpotsSquare;
    ExtCircuit8Len -= other.ExtCircuit8Len;
    ExtCircuit4Len -= other.ExtCircuit4Len;
    ExtPerimetr -= other.ExtPerimetr;
    IntCircuit8Len -= other.IntCircuit8Len;
    IntCircuit4Len -= other.IntCircuit4Len;
    IntPerimetr -= other.IntPerimetr;
    Square -= other.Square;
    Fullness -= other.Fullness;
    ShapeFactor -= other.ShapeFactor;
    MarkId = -1;
    // Фере
    MinDiametr -= other.MinDiametr;
    AngleMin -= other.AngleMin;
    MaxDiametr -= other.MaxDiametr;
    AngleMax -= other.AngleMax;
    AverageDiametr -= other.AverageDiametr;
    MeanSquareDiametr -= other.MeanSquareDiametr;
    // Радиус
    MaxRadius -= other.MaxRadius;
    MinRadius -= other.MinRadius;
    AverageRadius -= other.AverageRadius;
    MeanSquareRadius -= other.MeanSquareRadius;
    InertiaMoment -= other.InertiaMoment;
    RelInertiaMoment -= other.RelInertiaMoment;
    return (*this);
}

MorphDataReal &MorphDataReal::operator/=(const MorphDataReal &other)
{
    Spots /= other.Spots;
    SpotsSquare /= other.SpotsSquare;
    ExtCircuit8Len /= other.ExtCircuit8Len;
    ExtCircuit4Len /= other.ExtCircuit4Len;
    ExtPerimetr /= other.ExtPerimetr;
    IntCircuit8Len /= other.IntCircuit8Len;
    IntCircuit4Len /= other.IntCircuit4Len;
    IntPerimetr /= other.IntPerimetr;
    Square /= other.Square;
    Fullness /= other.Fullness;
    ShapeFactor /= other.ShapeFactor;
    MarkId = -1;
    // Фере
    MinDiametr /= other.MinDiametr;
    AngleMin /= other.AngleMin;
    MaxDiametr /= other.MaxDiametr;
    AngleMax /= other.AngleMax;
    AverageDiametr /= other.AverageDiametr;
    MeanSquareDiametr /= other.MeanSquareDiametr;
    // Радиус
    MaxRadius /= other.MaxRadius;
    MinRadius /= other.MinRadius;
    AverageRadius /= other.AverageRadius;
    MeanSquareRadius /= other.MeanSquareRadius;
    InertiaMoment /= other.InertiaMoment;
    RelInertiaMoment /= other.RelInertiaMoment;
    return (*this);
}

MorphDataReal &MorphDataReal::operator-=(const MorphDataReal &other)
{
    Spots -= other.Spots;
    SpotsSquare -= other.SpotsSquare;
    ExtCircuit8Len -= other.ExtCircuit8Len;
    ExtCircuit4Len -= other.ExtCircuit4Len;
    ExtPerimetr -= other.ExtPerimetr;
    IntCircuit8Len -= other.IntCircuit8Len;
    IntCircuit4Len -= other.IntCircuit4Len;
    IntPerimetr -= other.IntPerimetr;
    Square -= other.Square;
    Fullness -= other.Fullness;
    ShapeFactor -= other.ShapeFactor;
    MarkId = -1;
    // Фере
    MinDiametr -= other.MinDiametr;
    AngleMin -= other.AngleMin;
    MaxDiametr -= other.MaxDiametr;
    AngleMax -= other.AngleMax;
    AverageDiametr -= other.AverageDiametr;
    MeanSquareDiametr -= other.MeanSquareDiametr;
    // Радиус
    MaxRadius -= other.MaxRadius;
    MinRadius -= other.MinRadius;
    AverageRadius -= other.AverageRadius;
    MeanSquareRadius -= other.MeanSquareRadius;
    InertiaMoment -= other.InertiaMoment;
    RelInertiaMoment -= other.RelInertiaMoment;
    return (*this);
}

MorphDataReal &MorphDataReal::operator*=(const MorphDataReal &other)
{
    Spots *= other.Spots;
    SpotsSquare *= other.SpotsSquare;
    ExtCircuit8Len *= other.ExtCircuit8Len;
    ExtCircuit4Len *= other.ExtCircuit4Len;
    ExtPerimetr *= other.ExtPerimetr;
    IntCircuit8Len *= other.IntCircuit8Len;
    IntCircuit4Len *= other.IntCircuit4Len;
    IntPerimetr *= other.IntPerimetr;
    Square *= other.Square;
    Fullness *= other.Fullness;
    ShapeFactor *= other.ShapeFactor;
    MarkId = -1;
    // Фере
    MinDiametr *= other.MinDiametr;
    AngleMin *= other.AngleMin;
    MaxDiametr *= other.MaxDiametr;
    AngleMax *= other.AngleMax;
    AverageDiametr *= other.AverageDiametr;
    MeanSquareDiametr *= other.MeanSquareDiametr;
    // Радиус
    MaxRadius *= other.MaxRadius;
    MinRadius *= other.MinRadius;
    AverageRadius *= other.AverageRadius;
    MeanSquareRadius *= other.MeanSquareRadius;
    InertiaMoment *= other.InertiaMoment;
    RelInertiaMoment *= other.RelInertiaMoment;
    return (*this);
}

MorphDataReal &MorphDataReal::operator+=(const MorphData &other)
{
    Spots += other.Spots;
    SpotsSquare += other.SpotsSquare;
    ExtCircuit8Len += other.ExtCircuit8Len;
    ExtCircuit4Len += other.ExtCircuit4Len;
    ExtPerimetr += other.ExtPerimetr;
    IntCircuit8Len += other.IntCircuit8Len;
    IntCircuit4Len += other.IntCircuit4Len;
    IntPerimetr += other.IntPerimetr;
    Square += other.Square;
    Fullness += other.Fullness;
    ShapeFactor += other.ShapeFactor;
    MarkId = -1;
    // Фере
    MinDiametr += other.MinDiametr;
    AngleMin += other.AngleMin;
    MaxDiametr += other.MaxDiametr;
    AngleMax += other.AngleMax;
    AverageDiametr += other.AverageDiametr;
    MeanSquareDiametr += other.MeanSquareDiametr;
    // Радиус
    MaxRadius += other.MaxRadius;
    MinRadius += other.MinRadius;
    AverageRadius += other.AverageRadius;
    MeanSquareRadius += other.MeanSquareRadius;
    InertiaMoment += other.InertiaMoment;
    RelInertiaMoment += other.RelInertiaMoment;
    return (*this);
}

MorphDataReal MorphDataReal::operator*(const MorphDataReal &other)
{
    MorphDataReal retVal = (*this);
    retVal *= other;
    return retVal;
}

MorphDataReal MorphDataReal::operator/(const MorphDataReal &other)
{
    MorphDataReal retVal = (*this);
    retVal /= other;
    return retVal;
}

MorphDataReal MorphDataReal::operator/(qint64 num)
{
    MorphDataReal retVal = (*this);
    retVal /= num;
    return retVal;
}

MorphDataReal MorphDataReal::mophSqrt(const MorphDataReal &other)
{
    MorphDataReal retVal;
    retVal.Spots = sqrt(other.Spots);
    retVal.SpotsSquare = sqrt(other.SpotsSquare);
    retVal.ExtCircuit8Len = sqrt(other.ExtCircuit8Len);
    retVal.ExtCircuit4Len = sqrt(other.ExtCircuit4Len);
    retVal.ExtPerimetr = sqrt(other.ExtPerimetr);
    retVal.IntCircuit8Len = sqrt(other.IntCircuit8Len);
    retVal.IntCircuit4Len = sqrt(other.IntCircuit4Len);
    retVal.IntPerimetr = sqrt(other.IntPerimetr);
    retVal.Square = sqrt(other.Square);
    retVal.Fullness = sqrt(other.Fullness);
    retVal.ShapeFactor = sqrt(other.ShapeFactor);
    retVal.MarkId = -1;
    // Фере
    retVal.MinDiametr = sqrt(other.MinDiametr);
    retVal.AngleMin = sqrt(other.AngleMin);
    retVal.MaxDiametr = sqrt(other.MaxDiametr);
    retVal.AngleMax = sqrt(other.AngleMax);
    retVal.AverageDiametr = sqrt(other.AverageDiametr);
    retVal.MeanSquareDiametr = sqrt(other.MeanSquareDiametr);
    // Радиус
    retVal.MaxRadius = sqrt(other.MaxRadius);
    retVal.MinRadius = sqrt(other.MinRadius);
    retVal.AverageRadius = sqrt(other.AverageRadius);
    retVal.MeanSquareRadius = sqrt(other.MeanSquareRadius);
    retVal.InertiaMoment = sqrt(other.InertiaMoment);
    retVal.RelInertiaMoment = sqrt(other.RelInertiaMoment);
    return retVal;
}
