#ifndef TRESERVATIONRULES_H
#define TRESERVATIONRULES_H

#include <QtCore>
//#include "tthing.h"

namespace Core {
namespace Recognizer {

class TThing;

//стратегии резервирования
enum TReservationStrategy {rs_const=0, rs_average=1, rs_part=2 };
//---------------------------------------------------------------------------
//вспомогательный класс для TRecognizer
//правила резервирования памяти под вектора точек
class TReservationRules
{
    template<bool ThingPixel>
    friend class TRecognizer;
    qint64 all_sum;
    qint64 ext_sum;
    qint64 int_sum;

    qint64 all_n;
    qint64 ext_n;
    qint64 int_n;
public:
    TReservationStrategy AllStrategy;
    qint64 AllConst;
    qreal AllAverageK;
    qreal AllRectPart;

    TReservationStrategy ExtStrategy;
    qint64 ExtConst;
    qreal ExtAverageK;

    TReservationStrategy IntStrategy;
    qint64 IntConst;
    qreal IntAverageK;
    qreal IntExtPart;

private:
    TReservationRules();
    void ClearAverage();
    void UpdateAverage(const TThing *Thing);
    qint64 GetAllReserve(const TThing *Thing);
    qint64 GetExtReserve(const TThing *Thing);
    qint64 GetIntReserve(const TThing *Thing);
};

} // namespace Recognizer
} // namespace Core
#endif // TRESERVATIONRULES_H
