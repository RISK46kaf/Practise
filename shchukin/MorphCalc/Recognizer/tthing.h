#ifndef THING_H
#define THING_H
#include <QtCore>
//#include "treservationrules.h"

namespace Recognizer {

class TReservationRules;

class TThing
{
    //    template<pixB ThingPixel, TCoordSystemYDirection YDirection>
    template<bool ThingPixel>
    friend class TRecognizer;
    friend class TReservationRules;
    struct TPimpl{
        QVector<QPoint> ext_circuit_points;  //точки внешней границы
        QVector<QPoint> int_circuit_points;  //точки внутренней границы
        QVector<QPoint> all_points;          //все точки объекта
    };
    TPimpl* pimpl;
public:
    qint64 id;
    qint64 Xmin;
    qint64 Ymin;
    qint64 Xmax;
    qint64 Ymax;
    qint64 Spots;
    qint64 SpotsSquare;
    QPoint Start;

    qint64 ExtCircuit8Len; //количество точек, принадлежащих внешней 8связной границе обьекта
    qint64 ExtCircuit4Len; //количество точек, принадлежащих внутренней 4связной границе
    qint64 ExtPerimetr;    //внешний периметр
    qint64 IntCircuit8Len;
    qint64 IntCircuit4Len;
    qint64 IntPerimetr;
    qint64 Square;
    qreal  Fullness;       //заполненность
    qreal  ShapeFactor;    //нормированный коэффициент формы
    QPointF Center;        //координаты центра
    struct TRadius
    {
        qreal MaxRadius;
        qreal MinRadius;
        qreal AverageRadius;
        qreal MeanSquareRadius;
        QPoint MaxRadiusPoint;
        QPoint MinRadiusPoint;

        qreal InertiaMoment;
        qreal RelInertiaMoment;
        bool Valid;
        TRadius():MaxRadius(0),MinRadius(0),AverageRadius(0),MeanSquareRadius(0),
            InertiaMoment(0),RelInertiaMoment(0),Valid(false){}
    } Radius;

    struct TFere
    {
        qreal MinDiametr;
        qint64 AngleMin;
        QPair<QPoint, QPoint> CoupleMin;
        qreal MaxDiametr;
        qint64 AngleMax;
        QPair<QPoint, QPoint> CoupleMax;

        qreal AverageDiametr;
        qreal MeanSquareDiametr;
        bool Valid;
        TFere():MinDiametr(0),AngleMin(0),MaxDiametr(0),AngleMax(0),
            AverageDiametr(0),MeanSquareDiametr(0),Valid(false){}
    } Fere;

    mutable qint64 user_idata;
    mutable void* user_pdata;

    explicit TThing(qint64 number=0, qint64 xMin=0, qint64 yMin=0,
                    qint64 xMax=0, qint64 yMax=0); //задает номер объекта и обнуляет все поля
    TThing(const TThing& Thing);
    TThing& operator=(const TThing* Thing);
    ~TThing();

    operator bool()const
    {
        return (id!=0);
    }

    QVector<QPoint> ExtCircuitPoints()const;  //точки внешней границы
    QVector<QPoint> IntCircuitPoints()const;  //точки внутренней границы
    QVector<QPoint> AllPoints()const;         //все точки объекта

};

} // namespace Recognizer
#endif // THING_H
