#include "tthing.h"

using namespace Core::Recognizer;

QVector<QPoint> TThing::ExtCircuitPoints()const
{
    return pimpl->ext_circuit_points;
}

QVector<QPoint> TThing::IntCircuitPoints()const
{
    return pimpl->int_circuit_points;
}

QVector<QPoint> TThing::AllPoints()const
{
    return pimpl->all_points;
}

TThing::TThing(qint64 number, qint64 xMin, qint64 yMin, qint64 xMax, qint64 yMax):
    pimpl(new TThing::TPimpl),id(number),
    Xmin(xMin), Ymin(yMin), Xmax(xMax), Ymax(yMax), Spots(0), SpotsSquare(0),
    Start(0,0), ExtCircuit8Len(0), ExtCircuit4Len(0), ExtPerimetr(0),
    IntCircuit8Len(0), IntCircuit4Len(0), IntPerimetr(0),
    Square(0), Fullness(0), ShapeFactor(0), Center(0,0),
    user_idata(0), user_pdata(NULL)
{
}

//по здравому рассуждению давать строгую гарантию безопасности при присваивании нет смысла,
//поэтому реализуем простое копирование и простое присваивание
//(к слову, леер дает строгую гарантию безопасности при присваивании)
TThing::TThing(const TThing& Thing):pimpl(new TThing::TPimpl)
{
    this->operator=(Thing);
}

TThing& TThing::operator=(const TThing* Thing)
{
    *pimpl = *Thing->pimpl;

    id = Thing->id;
    Xmin = Thing->Xmin;
    Ymin = Thing->Ymin;
    Xmax = Thing->Xmax;
    Ymax = Thing->Ymax;
    Spots = Thing->Spots;
    SpotsSquare = Thing->SpotsSquare;
    Start = Thing->Start;

    ExtCircuit8Len = Thing->ExtCircuit8Len;
    ExtCircuit4Len = Thing->ExtCircuit4Len;
    ExtPerimetr = Thing->ExtPerimetr;
    IntCircuit8Len = Thing->IntCircuit8Len;
    IntCircuit4Len = Thing->IntCircuit4Len;
    IntPerimetr = Thing->IntPerimetr;
    Square = Thing->Square;
    Fullness = Thing->Fullness;
    ShapeFactor = Thing->ShapeFactor;
    Center = Thing->Center;

    Radius = Thing->Radius;
    Fere = Thing->Fere;

    user_idata = Thing->user_idata;
    user_pdata = Thing->user_pdata;

    return *this;
}

TThing::~TThing()
{
    delete pimpl;
}
