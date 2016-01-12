#include "treservationrules.h"
#include "tthing.h"

using namespace Recognizer;

TReservationRules::TReservationRules():
    all_sum(0),ext_sum(0),int_sum(0), all_n(0), ext_n(0), int_n(0),
    AllStrategy(rs_average),AllConst(256),AllAverageK(1),AllRectPart(0.5),
    ExtStrategy(rs_average),ExtConst( 64),ExtAverageK(1),
    IntStrategy(rs_average),IntConst( 16),IntAverageK(1),IntExtPart(0.1)
{}
void TReservationRules::ClearAverage()
{
    all_sum=0;
    ext_sum=0;
    int_sum=0;
    all_n=0;
    ext_n=0;
    int_n=0;
}

void TReservationRules::UpdateAverage(const TThing* Thing)
{
    if(AllStrategy==rs_average)
    {
        all_sum+=Thing->pimpl->all_points.size();
        ++all_n;
    }
    if(ExtStrategy==rs_average)
    {
        ext_sum+=Thing->pimpl->ext_circuit_points.size();
        ++ext_n;
    }
    if(IntStrategy==rs_average)
    {
        qint64 S=Thing->pimpl->int_circuit_points.size();
        if(S)
        {
            int_sum+=S; ++int_n;
        }
    }
}

qint64 TReservationRules::GetAllReserve(const TThing* Thing)
{
    float res;
    switch(AllStrategy)
    {
    case rs_const   : return AllConst;
    case rs_average : if(all_n)
        {
            res=static_cast<float>(all_sum/all_n);
            res*=AllAverageK;
            return res+0.5;
        }
        else
        {
            return AllConst;
        }
    case rs_part    : res=(Thing->Xmax-Thing->Xmin+1)*(Thing->Ymax-Thing->Ymin+1);
        res*=AllRectPart;
        return res+0.5;
    }
    return 0;
}

qint64 TReservationRules::GetExtReserve(const TThing * )
{
    float res;
    switch(ExtStrategy)
    {
    case rs_const   : return ExtConst;
    case rs_average : if(ext_n)
        {
            res=static_cast<float>(ext_sum/ext_n);
            res*=ExtAverageK;
            return res+0.5;
        }
        else
        {
            return ExtConst;
        }
    case rs_part    : return 0;//для вектора точек внешней границы
        //стратегия rs_parts не имеет смысла
    }
    return 0;
}

qint64 TReservationRules::GetIntReserve(const TThing *Thing)
{
    float res;
    switch(IntStrategy)
    {
    case rs_const   : return IntConst;
    case rs_average : if(int_n)
        {
            res=static_cast<float>(int_sum/int_n);
            res*=IntAverageK;
            return res+0.5;
        }
        else
        {
            return IntConst;
        }
    case rs_part    : res=Thing->pimpl->ext_circuit_points.size();
        res*=IntExtPart;
        return res;
    }
    return 0;
}

