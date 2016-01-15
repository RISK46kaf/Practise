#include "trecognizer.h"

using namespace Core::Recognizer;

qreal m_sqrt2=     1.41421356237309504880; //  sqrt(2)
qreal m_1_2sqrtpi= 0.28209479177387814347; //  1/(2*sqrt(pi))
qreal m_pi=        3.14159265358979323846; //  pi
qreal m_2pi=       6.28318530717958647693; //  2*pi

struct TSincos
{
    qreal x[180];
    qreal y[180];
    TSincos();
};

TSincos::TSincos()
{
    const qreal k=m_pi/180;
    for(qint64 i=0;i<180;++i)
    {
        y[i]=std::sin(k*i);
        x[i]=std::cos(k*i);
    }
}

template<bool ThingPixel>
struct TRecognizer<ThingPixel>::TPimpl
{
    TLayerRec thing_layer;
    TThingVector thing_vector;
    TPimpl()
    {
        thing_layer =  TLayerRec(1,1);
        thing_layer.Pixel(0,0).zero();
        thing_vector.push_back(/*TThing()*/new TThing());//один фиктивный элемент
    }
};

template<bool ThingPixel>
TRecognizer<ThingPixel>::TRecognizer():
    pimpl(new TRecognizer::TPimpl)
{
#ifdef _DEBUG
    qDebug("TRecognizer<ThingPixel>::TRecognizer()");
#endif
}

template<bool ThingPixel>
TRecognizer<ThingPixel>::TRecognizer(const TRecognizer& R):
    pimpl(new TRecognizer::TPimpl)
{
    *pimpl=*R.pimpl;
    RegMode=R.RegMode;
    ReservationRules=R.ReservationRules;
}

template<bool ThingPixel>
TRecognizer<ThingPixel>& TRecognizer<ThingPixel>::operator=(const TRecognizer& R)
{
    *pimpl=*R.pimpl;
    RegMode=R.RegMode;
    ReservationRules=R.ReservationRules;
    return *this;
}

template<bool ThingPixel>
TRecognizer<ThingPixel>::~TRecognizer()
{
    qDeleteAll(pimpl->thing_vector);
    delete pimpl;
}

template<bool ThingPixel>
const TLayerRec& TRecognizer<ThingPixel>::ThingLayer() const
{
    return pimpl->thing_layer;
}

template<bool ThingPixel>
TThingVector TRecognizer<ThingPixel>::ThingVector()const
{
    return pimpl->thing_vector;
}

template<bool ThingPixel>
void TRecognizer<ThingPixel>::Clear(bool lay, bool vec)
{
    if(lay)
        pimpl->thing_layer.resize(1,1,pixrec());
    pimpl->thing_layer.clear();

    if(vec)
    {
        qDeleteAll(pimpl->thing_vector);
        pimpl->thing_vector.push_back(new TThing());
//        TThingVector().swap(pimpl->thing_vector);
    }
    pimpl->thing_vector.resize(1);
}

template<bool ThingPixel>
void TRecognizer<ThingPixel>::Reserve(qint64 things_count)
{
    pimpl->thing_vector.reserve(things_count+1);
}

template<bool ThingPixel>
void TRecognizer<ThingPixel>::Unreserve()
{
    TThingVector(pimpl->thing_vector).swap(pimpl->thing_vector);
}

template<bool ThingPixel>
void TRecognizer<ThingPixel>::FindThings(const TLayerB& Src)
{
    //очистим старое содержимое
    pimpl->thing_vector.resize(1);//нулевой элемент - фиктивный
    pimpl->thing_layer.resize(Src.size(),pixrec());
    pimpl->thing_layer.clear();

    RegMode.SetLast();
    ReservationRules.ClearAverage();//сбросили накопленные значения

    //    TImmPlotterT<TLayerB,csDebugCheck,YDirection> PlotterSrc(Src);
    //    TPlotterT<TLayerRec,csDebugCheck,YDirection> PlotterDst(pimpl->thing_layer);
    TLayerRec* Dst = &(pimpl->thing_layer);

    qint64 w = Src.width();
    qint64 h = Src.height();

    //обрабатываем черные точки на белом фоне
    for(qint64 y=0;y<h;++y )
    {
        for(qint64 x=0;x<w;++x )
        {
            if( (Src.Pixel(x,y))==thing_pixel )
            {
                if( Dst->Pixel(x,y).OnBack() )// эта точка еще не принадлежит ни одному пятну
                {
                    pimpl->thing_vector.push_back(new TThing());
                    TThing* thing=pimpl->thing_vector.back();

                    if(RegMode.Ext)
                    {
                        qint64 res=ReservationRules.GetExtReserve(thing);
                        thing->pimpl->ext_circuit_points.reserve(res);
                        //зарезервировали память под точки внешней границы
                    }

                    qint64 ThingNumber=pimpl->thing_vector.size()-1; // <- Thing'и нумеруются с единицы
                    this->FindCircuit(Src, x, y, thing, ThingNumber, true);

                    if(RegMode.All)
                    {
                        qint64 res=ReservationRules.GetAllReserve(thing);
                        thing->pimpl->all_points.reserve(res);
                        //зарезервировали память под все точки вектора
                    }

                    this->FindEntry(Src);

                    ReservationRules.UpdateAverage(thing);//обновим накопления
                }
            }
        } // for x
    } //for y

    //пометим крайние пиксели
    qint64 w1=Src.width() - 1;
    qint64 h1=Src.height() - 1;
    for(qint64 i=0;i<w;++i)
    {
        Dst->Pixel(i,0).bits|=0x4400;   //край сверху
        Dst->Pixel(i,h1).bits|=0x4100; //край снизу
    }
    for(qint64 i=0;i<h;++i)
    {
        Dst->Pixel(0,i).bits|=0x4800;   //край слева
        Dst->Pixel(w1,i).bits|=0x4200; //край справа
    }
}

template<bool ThingPixel>
void TRecognizer<ThingPixel>::
FindCircuit(const TLayerB& Src, qint64 StartX, qint64 StartY,
            TThing* Thing, qint64 ThingNumber, bool External)
{
    ////////////////////////////////////////////////////////////////////////
    // Расчеты производятся для геометрической системы координат:         //
    // это касается направления стороны света и поворотов.                //
    // Что интересно, в компьютерной системе координат все тоже работает, //
    // но имена переменных и комментарии становятся неадекватными.        //
    ////////////////////////////////////////////////////////////////////////
    //
    // Начальные условия:
    //   - стоим на точке цвета thing_pixel
    //   - смотрим не север
    //   - слева точка цвета не равного thing_pixel
    //
    // Случай 1. Находится внешняя граница (периметр) нашего объекта.
    //           В процессе обхода мы находимся внутри окружающих нас
    //           точек цвета не равного thing_pixel
    //
    // Случай 2. Пятно объекта цвета не равного thing_pixel
    //           находится внутри нашего объекта обходится с внешней стороны.
    //
    /////////////////////////////////////////////////////////////////////////

    QPoint PixMIN(Src.width() - 1,Src.height() - 1);
    QPoint PixMAX(0,0);
    QPoint PixNOW(StartX, StartY); // текущая точка
    QPoint PixLEFT;    // точка слева от нашей (относительно направления)
    QPoint PixFORWARD; // точка впереди нашей (относительно направления)
    qint64    Perimetr8 = 0;
    qint64 forPerimetr4 = 0;

    TLayerRec* Dst = &(pimpl->thing_layer);

    bool Granted; // <- говорит о том, "вступим" ли мы за границы нашего рисунка
    TDirection dNow = dNorth; // <- сначала всегда смотрим ВВЕРХ

    short westwall, northwall, eastwall, southwall, borderbit;
    bool registration;
    bool unique;
    switch(External)
    {
    case false://внутренняя граница
        westwall =0x2080;  //фон слева
        northwall=0x2040;  //фон сверху
        eastwall =0x2020;  //фон справа
        southwall=0x2010;  //фон снизу
        borderbit=0x2000;
        registration=RegMode.Int;
        unique=RegMode.IntUnique;
        break;
    case true: //внешняя граница
        westwall =0x1008;  //фон слева
        northwall=0x1004;  //фон сверху
        eastwall =0x1002;  //фон справа
        southwall=0x1001;  //фон снизу
        borderbit=0x1000;
        registration=RegMode.Ext;
        unique=RegMode.ExtUnique;
        break;
    };

    bool anotherpoint=true;

    //НАЧАЛО ГЛАВНОГО ЦИКЛА ОБХОДА:
    do
    {
        //1. Зарегистрируем нашу точку
        if(anotherpoint)
        {
            //1.А если необходимо добавляем точку в вектор
            if(registration)
                switch(unique)
                {
                case true :  if(! (Dst->Pixel(PixNOW).bits & borderbit) )
                    {
                        //если по этой точке еще не проходили
                        Thing->pimpl->ext_circuit_points.push_back(PixNOW);
                    }
                    break;
                case false : Thing->pimpl->ext_circuit_points.push_back(PixNOW);
                    break;
                }

            //1.Б Запишем в матрицу объектов, что это точка данного объекта
            Dst->Pixel(PixNOW).SetThing(ThingNumber);
            //и что это точка границы
            Dst->Pixel(PixNOW).bits|=borderbit;

            //1.В При необходимости изменим значения точек описанного прямоугольника
            if(PixNOW.x() < PixMIN.x())
                PixMIN.setX(PixNOW.x());
            if(PixNOW.y() < PixMIN.y())
                PixMIN.setY(PixNOW.y());
            if(PixNOW.x() > PixMAX.x())
                PixMAX.setX(PixNOW.x());
            if(PixNOW.y() > PixMAX.y())
                PixMAX.setY(PixNOW.y());
        }

        //2. Определим точку слева от нас
        switch( dNow )
        {
        case dNorth: PixLEFT.setX(PixNOW.x() - 1);
            PixLEFT.setY(PixNOW.y());
            Granted = (PixLEFT.x() >= 0);
            break;
        case dEast:  PixLEFT.setX(PixNOW.x());
            PixLEFT.setY(PixNOW.y() + 1);
            Granted = ((quint64)PixLEFT.y() < Src.height());
            break;
        case dSouth: PixLEFT.setX(PixNOW.x() + 1);
            PixLEFT.setY(PixNOW.y());
            Granted = ((quint64)PixLEFT.x() < Src.width());
            break;
        case dWest:  PixLEFT.setX(PixNOW.x());
            PixLEFT.setY(PixNOW.y() - 1);
            Granted = (PixLEFT.y() >= 0);
            break;
        };

        //3. Если точка слева есть точка объекта, идем на нее
        if( (Granted)&&((Src.Pixel(PixLEFT))==thing_pixel) )
        {
            TurnLeft(dNow);
            PixNOW=PixLEFT;
            anotherpoint=true;
            ++forPerimetr4;
        }

        //3. Раз влево повернуть не удалось, то пробуем идти вперед
        else
        {
            //3.А определим точку впереди и запишем в матрицу объектов, что влево нельзя
            switch( dNow )
            {
            case dNorth: PixFORWARD.setX(PixNOW.x());
                PixFORWARD.setY(PixNOW.y() + 1);
                Granted = ((quint64)PixFORWARD.y() < Src.height());
                Dst->Pixel(PixNOW).bits |= westwall;  //фон слева
                break;
            case dEast:  PixFORWARD.setX(PixNOW.x() + 1);
                PixFORWARD.setY(PixNOW.y());
                Granted = ((quint64)PixFORWARD.x() < Src.width());
                Dst->Pixel(PixNOW).bits |= northwall;  //фон сверху
                break;
            case dSouth: PixFORWARD.setX(PixNOW.x());
                PixFORWARD.setY(PixNOW.y() - 1);
                Granted = (PixFORWARD.y() >= 0);
                Dst->Pixel(PixNOW).bits |= eastwall;  //фон справа
                break;
            case dWest:  PixFORWARD.setX(PixNOW.x() - 1);
                PixFORWARD.setY(PixNOW.y());
                Granted = (PixFORWARD.x() >= 0);
                Dst->Pixel(PixNOW).bits |= southwall;  //фон снизу
                break;
            };

            //3.Б Если и прямо нельзя, то стоя не месте, поворачиваем направо
            //и ничего больше на данной итерации ГЛАВНОГО ЦИКЛА не делаем
            if ( (!Granted) || ((Src.Pixel(PixFORWARD))!=thing_pixel) )
            {
                TurnRight(dNow);
                anotherpoint=false;
            }
            //3.В Если же прямо можно, то идем туда
            else
            {
                PixNOW = PixFORWARD;
                anotherpoint=true;
                ++Perimetr8;
            };
        }; //конец шага 3
    }
    while( (PixNOW.x() != StartX) || (PixNOW.y() != StartY) || (dNow!= dNorth) );
    //КОНЕЦ ГЛАВНОГО ЦИКЛА ОБХОДА:
    //вернулись в ту же точку, имеем то же направление

    if( (!External)&&(registration)&&(!unique) )
    {
        //если стоит режим регистрация неуникальных пикселей внутренней границы,
        //то сделаем замыкание - поместим в конец вектора последнюю точку
        Thing->pimpl->ext_circuit_points.push_back(PixNOW);
    }

    //особый случай - объект из одной точки
    if(!Perimetr8)
    {
        //      Perimetr8=1;
        PixMIN.setX(StartX);
        PixMIN.setY(StartY);
        PixMAX.setX(StartX);
        PixMAX.setY(StartY);
        Dst->Pixel(PixNOW).SetThing(ThingNumber);
        Dst->Pixel(PixNOW).bits|=0x100F;

        if( (External)&&(registration)&&(!unique) )
        {
            //если стоит режим регистрация неуникальных пикселей внешней границы,
            //то сделаем замыкание - поместим в конец вектора последнюю точку
            Thing->pimpl->ext_circuit_points.push_back(PixNOW);
        }
    }

    Thing->id=ThingNumber;
    Thing->Xmin=PixMIN.x();
    Thing->Xmax=PixMAX.x();
    Thing->Ymin=PixMIN.y();
    Thing->Ymax=PixMAX.y();
    Thing->Start.setX(StartX);
    Thing->Start.setY(StartY);
    Thing->ExtCircuit8Len=Perimetr8;
    Thing->ExtCircuit4Len=Perimetr8+forPerimetr4;


    Thing->ExtPerimetr=(Perimetr8)?
                (Thing->ExtCircuit8Len +(m_sqrt2 / 3 )*(Thing->ExtCircuit4Len-Thing->ExtCircuit8Len)+4+0.5):
                4;
}

template<bool ThingPixel>
void TRecognizer<ThingPixel>::FindEntry(const TLayerB& Src)
{
    TLayerRec* Dst = &(pimpl->thing_layer);

    //   void* ptr=&PlotterDst;

    TThing *Thing=pimpl->thing_vector.back();

    //важен переход от беззнаковых чисел к знаковым
    int Xmin = Thing->Xmin;
    int Ymin = Thing->Ymin;
    int Xmax = Thing->Xmax;
    int Ymax = Thing->Ymax;

    qint64 Xsum=0;
    qint64 Ysum=0;
    ////////////////////////////////////////////////////////////
    //  Мы должны идти "с севера на юг" и "с востока на запад"//
    //  т.к. если мы натыкаемся на ВНУТРЕННЮЮ пору,           //
    //  то, хотим делать ВНУТРЕННЮЮ границу используя         //
    //  всё тот же метод FindCircuit ( а в нем                //
    //  первоначальным направлением является "dNorth" )       //
    ////////////////////////////////////////////////////////////

    qint64 ThingNumber=Thing->id;
    qint64 Square=0;
    qint64 SpotsSquare=0;
    //   enum TState {onspot, onthing, other};
    //   TState state=other;
    bool onspot=false;
    for( int Yi = Ymin; Yi <= Ymax; ++Yi )
    {
        int Xi = Xmax;
        while( Xi>=Xmin )
        {
            // Идем до первой встречной границы с востоком (неважно внешней или внутренней)
            // нашего объекта, проходя мимо как БЕЛЫХ, так и ЧЕРНЫХ точек.
            if( !(Dst->Pixel(Xi,Yi).OnRightCircuit(ThingNumber)) )
            {
                --Xi;
                SpotsSquare+=onspot;
                continue;
            };

            ////////////////////////////////////////
            //  щас мы стоим на какой-то БЕЛОЙ,   //
            //  ОЧЕРЕДНОЙ_ПЕРВОЙ_СПРАВА клеточке  //
            ////////////////////////////////////////

            onspot=false;
            while( true )
            {
                ++Square;
                Xsum+=Xi;
                Ysum+=Yi;

                if(RegMode.All)
                    Thing->pimpl->all_points.push_back(QPoint(Xi,Yi));

                if (!Xi)
                {
                    --Xi;
                    break;
                };

                if ( Src.Pixel((Xi-1),Yi)==thing_pixel )
                {
                    //если слева от нас тоже точка объекта
                    --Xi;
                    Dst->Pixel(Xi,Yi).SetThing(ThingNumber);
                    continue;
                }
                else //если слева точка фона
                {
                    if(Dst->Pixel(Xi,Yi).bits & 0x0088)
                    {
                        //мы стоим на левой границе (внешней или внутренней)
                        //т.е. она была отмечена при обходе по периметру
                        --Xi;
                    }
                    else
                    {
                        //пиксель, на котором мы стоим - ещё НЕ обозначен как граничный
                        //значит, попалось пятно внутри объекта
                        //запускаем для этой точки алгоритм обхода контура...

                        TThing Tmp; //это внутреннее препятствие
                        qint64 ThingNumber=pimpl->thing_vector.size()-1;//это номер частицы
                        if(RegMode.Int)
                        {
                            qint64 res=ReservationRules.GetIntReserve(Thing);
                            Tmp.pimpl->ext_circuit_points.reserve(res);
                        }

                        FindCircuit(Src, Xi, Yi, &Tmp, ThingNumber, false);

                        ++Thing->Spots;
                        Thing->IntCircuit4Len+=Tmp.ExtCircuit4Len;
                        Thing->IntCircuit8Len+=Tmp.ExtCircuit8Len;
                        Thing->IntPerimetr+=Tmp.ExtPerimetr;
                        if(RegMode.Int)
                        {
                            qint64 res=ReservationRules.GetIntReserve(Thing);
                            if(res<Tmp.pimpl->ext_circuit_points.size())
                                res=Tmp.pimpl->ext_circuit_points.size();
                            Thing->pimpl->int_circuit_points.reserve(res);

                            for(qint64 i=0;i<Tmp.pimpl->ext_circuit_points.size();++i)
                            {
                                Thing->pimpl->int_circuit_points.push_back(Tmp.pimpl->ext_circuit_points[i]);
                            }
                        }
                        --Xi;
                    }
                    onspot=Dst->Pixel(Xi+1,Yi).bits & 0x0080;
                    //внутренняя граница слева, то это пятно
                    break;
                }
            }
        } // while(Xi<=Xmin)
    } // for

    if(!Square)
        throw "zero square - impossible";

    Thing->Square=Square;
    Thing->SpotsSquare=SpotsSquare;
    Thing->Fullness=static_cast<qreal>(Square)/(Square+SpotsSquare);
    Thing->Center.setX(static_cast<qreal>(Xsum)/Square);
    Thing->Center.setY(static_cast<qreal>(Ysum)/Square);
    Thing->ShapeFactor=static_cast<qreal>(Thing->ExtPerimetr) / std::sqrt(static_cast<qreal>(Thing->Square) );
    Thing->ShapeFactor*=m_1_2sqrtpi;//нормировка
}

////определение моментов инерции для всех объектов
template<bool ThingPixel>
void TRecognizer<ThingPixel>::CalculateRadius()
{
    //перед вызовом этого метода должен отработать метод FindThings
    qint64 size=pimpl->thing_vector.size();
    if(size<=1)return;
    TLayerRec* Dst = &(pimpl->thing_layer);
    for(qint64 n=1;n<size;++n)
    {
        TThing* Thing=pimpl->thing_vector[n];
        qreal thing_mi=0;
        qreal SumRad=0;
        qreal SumRad2=0;
        qreal MaxRad=0;
        qreal MinRad=std::numeric_limits<qreal>::max();
        QPoint MaxRadPoint, MinRadPoint;
        qint64 PointsCount=0;

        for(qint64 y=Thing->Ymin;y<=Thing->Ymax;++y)
        {
            for(qint64 x=Thing->Xmin;x<=Thing->Xmax;++x)
            {
                if(Dst->Pixel(x,y).OnThing(n))
                {
                    //пиксель на нашем объекте
                    qreal dist2=(Thing->Center.x()-x)*(Thing->Center.x()-x)+
                            (Thing->Center.y()-y)*(Thing->Center.y()-y);
                    thing_mi+=dist2;

                    if(Dst->Pixel(x,y).OnExtCircuit())
                    {
                        //пиксель на внешней границе
                        ++PointsCount;

                        SumRad2+=dist2;
                        qreal dist=std::sqrt(dist2);
                        SumRad+=dist;

                        if(dist>=MaxRad)
                        {
                            MaxRad=dist;
                            MaxRadPoint=QPoint(x,y);
                        }
                        if(dist<MinRad)
                        {
                            MinRad=dist;
                            MinRadPoint=QPoint(x,y);
                        }
                    }
                }//if(OnThing)
            }//for(x)
        }//for(y)

        Thing->Radius.MaxRadius=MaxRad;
        Thing->Radius.MinRadius=MinRad;
        Thing->Radius.MaxRadiusPoint=MaxRadPoint;
        Thing->Radius.MinRadiusPoint=MinRadPoint;
        Thing->Radius.AverageRadius=SumRad/PointsCount;
        Thing->Radius.MeanSquareRadius=std::sqrt(SumRad2/PointsCount);

        qreal circ_mi=static_cast<qreal>(Thing->Square*Thing->Square)/(m_2pi);
        Thing->Radius.InertiaMoment=thing_mi;
        Thing->Radius.RelInertiaMoment=thing_mi/circ_mi;
        Thing->Radius.Valid=true;
        int stub;
        Q_UNUSED(stub)
    }//for(n)
}

//определение осей всех объектов
template<bool ThingPixel>
void TRecognizer<ThingPixel>::CalculateFere()
{
    static TSincos sincos;
    qreal c[180];
    {
        static const qreal zerof=0.0;
        std::fill(c,c+90,zerof);
        const qreal whf=static_cast<qreal>(pimpl->thing_layer.height()+pimpl->thing_layer.width());
        std::fill(c+90,c+180,whf);
    }

    if(!RegMode.last_ext)
        return;
    const qint64 things_count=pimpl->thing_vector.size();
    if(!things_count)
        return;
//    TLayerRec* Dst = &(pimpl->thing_layer);
    for(qint64 n=1;n<things_count;++n)
    {
        TThing* Thing=pimpl->thing_vector[n];
        Thing->Fere.Valid=true;
        const QVector<QPoint>& vp=Thing->pimpl->ext_circuit_points;
        qint64 size=vp.size();
        if(!RegMode.last_extunique)
            --size;//чтобы не учитывать замыкающий пиксель (он совпадает с первым)

        qreal MinFere=std::numeric_limits<qreal>::max();
        qreal MaxFere=0;
        qreal SumFere=0;
        qreal SumFere2=0;
        qreal AngleMin=0;
        qreal AngleMax=0;
        std::pair<qint64,qint64> IndicesMin;
        std::pair<qint64,qint64> IndicesMax;
        for(qint64 angle=0;angle<180;++angle)
        {
            qreal dmin=std::numeric_limits<qreal>::max();
            qreal dmax=0;
            qint64 imin=0;
            qint64 imax=0;
            for(qint64 i=0;i<size;++i)
            {
                qreal d=sincos.x[angle]*vp[i].y()+sincos.y[angle]*vp[i].x()+c[angle];
                if(d<dmin)
                {
                    dmin=d;
                    imin=i;
                }
                if(d>dmax)
                {
                    dmax=d;
                    imax=i;
                }
                int stub;
                Q_UNUSED(stub)
            }//for(i)
            //закончили обход объекта в одной проекции
            qreal Fere=std::fabs(dmax-dmin)+1;
            if(Fere<MinFere)
            {
                MinFere=Fere;
                AngleMin=angle;
                IndicesMin=std::make_pair(imin,imax);
            }
            if(Fere>MaxFere)
            {
                MaxFere=Fere;
                AngleMax=angle;
                IndicesMax=std::make_pair(imin,imax);
            }
            SumFere+=Fere;
            SumFere2+=(Fere*Fere);
        }//for(k)
        //закончили обход всех проекций
        Thing->Fere.MaxDiametr=MaxFere;
        AngleMax=(AngleMax>=90)?(AngleMax-90):(AngleMax+90);
        Thing->Fere.AngleMax=AngleMax;
        Thing->Fere.CoupleMax=QPair<QPoint,QPoint>(vp[IndicesMax.first],
                vp[IndicesMax.second]);

        Thing->Fere.MinDiametr=MinFere;
        AngleMin=(AngleMin>=90)?(AngleMin-90):(AngleMin+90);
        Thing->Fere.AngleMin=AngleMin;
        Thing->Fere.CoupleMin=QPair<QPoint,QPoint>(vp[IndicesMin.first],
                vp[IndicesMin.second]);

        Thing->Fere.AverageDiametr=(SumFere/180);
        Thing->Fere.MeanSquareDiametr=std::sqrt(SumFere2/180);
        int stub;
        Q_UNUSED(stub)
    }
}

//сбросить вектора с координатами пикселей объектов
template<bool ThingPixel>
void TRecognizer<ThingPixel>::
ClearRegPoints(bool All, bool Ext, bool Int)
{
    All=All&&RegMode.last_all;
    Ext=Ext&&RegMode.last_ext;
    Int=Int&&RegMode.last_int;
    const qint64 things_count=pimpl->thing_vector.size();
    for(qint64 n=1;n<things_count;++n)
    {
        TThing* Thing=pimpl->thing_vector[n];
        if(All)
            QVector<QPoint>().swap(Thing->pimpl->all_points);
        if(Ext)
            QVector<QPoint>().swap(Thing->pimpl->ext_circuit_points);
        if(Int)
            QVector<QPoint>().swap(Thing->pimpl->int_circuit_points);
    }
    RegMode.last_all=All;
    RegMode.last_ext=Ext;
    RegMode.last_int=Int;
}

template<bool ThingPixel>
const TThing& TRecognizer<ThingPixel>::GetThing(qint64 x, qint64 y)const
{
    if(pimpl->thing_layer.containsPoint(x,y))
    {
        pixrec& p=pimpl->thing_layer.Pixel(x,y);
        if(p.OnThing())
            return *(pimpl->thing_vector)[p.id];
    }
    return *(pimpl->thing_vector)[0];
}

//проверяем,что все пиксели каждого thing'а лежат внутри прямоугольника
//проверяем,что площадь Thing'а равна указанной
template<bool ThingPixel>
bool TRecognizer<ThingPixel>::SelfTest()
{
    TLayerRec* Dst = &(pimpl->thing_layer);
    for(qint64 thNumber=1; thNumber<pimpl->thing_vector.size(); ++thNumber)
    {
        qint64 sq=0;
        for(quint64 y=0; y<pimpl->thing_layer.height(); ++y)
        {
            for(quint64 x=0; x<pimpl->thing_layer.width(); ++x)
            {
                if(Dst->Pixel(x,y).id==thNumber)
                {
                    ++sq;//ув. площадь
                    if (
                            (x <= (quint64)pimpl->thing_vector[thNumber]->Xmax) &&
                            (x >= (quint64)pimpl->thing_vector[thNumber]->Xmin) &&
                            (y <= (quint64)pimpl->thing_vector[thNumber]->Ymax) &&
                            (y >= (quint64)pimpl->thing_vector[thNumber]->Ymin)
                            )
                    {
                        int stub;
                        Q_UNUSED(stub)
                    }
                    else
                    {
                        return false;// ошибка
                    }
                }//pixel check
            }//x
        }//y
        if (sq != pimpl->thing_vector[thNumber]->Square)
            return false;
    }
    return true;
}
template<bool ThingPixel>
template<class BinaryFunctor>
BinaryFunctor TRecognizer<ThingPixel>::
for_each_point(const TThing* Thing, BinaryFunctor F)
{
    if(!Thing)
        return F;
    if(RegMode.LastAll)
    {
        QVector<QPoint>::const_iterator i=Thing->AllPoints().begin();
        QVector<QPoint>::const_iterator end=Thing->AllPoints().end();
        while(i!=end)
        {
            F(i->x(), i->y());
            ++i;
        }
    }
    else
    {
        int sXmin=Thing->Xmin;
        for(qint64 y=Thing->Ymin;y<=Thing->Ymax;++y)
            for(int x=Thing->Xmax;x>=sXmin;--x)
            {
                pixrec p=ThingLayer()(x,y);
                if(p.OnThing(Thing->id))
                    F(x,y);
            }
    }//else
    return F;
}

template<bool ThingPixel>
template<class TernaryFunctor>
TernaryFunctor TRecognizer<ThingPixel>::
for_each_point_bits(const TThing* Thing, TernaryFunctor F)
{
    if(!Thing)
        return F;
    const TLayerRec& L=this->ThingLayer();
    if(RegMode.LastAll)
    {
        QVector<QPoint>::const_iterator i=Thing->AllPoints().begin();
        QVector<QPoint>::const_iterator end=Thing->AllPoints().end();
        while(i!=end)
        {
            const pixrec& p=L.Pixel(*i);
            F(i->x(), i->y(), p.bits);
            ++i;
        }
    }
    else
    {
        int sXmin=Thing->Xmin;
        for(qint64 y=Thing->Ymin;y<=Thing->Ymax;++y)
            for(int x=Thing->Xmax;x>=sXmin;--x)
            {
                const pixrec& p=L.Pixel(x,y);
                if(p.OnThing(Thing->id))
                    F(x,y,p.bits);
            }
    }//else
    return F;
}

template<bool ThingPixel>
template<class BinaryFunctor>
BinaryFunctor TRecognizer<ThingPixel>::
for_each_extcircuitpoint(const TThing* Thing, BinaryFunctor F)
{
    if(!Thing)
        return F;
    if(RegMode.LastExt)
    {
        QVector<QPoint>::const_iterator i=Thing->ExtCircuitPoints().begin();
        QVector<QPoint>::const_iterator end=Thing->ExtCircuitPoints().end();
        while(i!=end)
        {
            F(i->x(),i->y());
            ++i;
        }
    }
    else
    {
        int sXmin=Thing->Xmin;
        for(qint64 y=Thing->Ymin;y<=Thing->Ymax;++y)
            for(int x=Thing->Xmax;x>=sXmin;--x)
            {
                pixrec p=ThingLayer()(x,y);
                if(p.OnExtCircuit() && p.OnThing(Thing->id))
                    F(x,y);
            }
    }//else
    return F;
}

template<bool ThingPixel>
template<class TernaryFunctor>
TernaryFunctor TRecognizer<ThingPixel>::
for_each_extcircuitpoint_bits(const TThing* Thing, TernaryFunctor F)
{
    if(!Thing)
        return F;
    if(RegMode.LastExt)
    {
        QVector<QPoint>::const_iterator i=Thing->ExtCircuitPoints().begin();
        QVector<QPoint>::const_iterator end=Thing->ExtCircuitPoints().end();
        while(i!=end)
        {
            pixrec p=ThingLayer(*i);
            F(i->x(), i->y(), p.bits);
            ++i;
        }
    }
    else
    {
        int sXmin=Thing->Xmin;
        for(qint64 y=Thing->Ymin;y<=Thing->Ymax;++y)
            for(int x=Thing->Xmax;x>=sXmin;--x)
            {
                pixrec p=ThingLayer(x,y);
                if(p.OnExtCircuit() && p.OnThing(Thing->id))
                    F(x,y,p.bits);
            }
    }//else
    return F;
}

template<bool ThingPixel>
template<class BinaryFunctor>
BinaryFunctor TRecognizer<ThingPixel>::
for_each_intcircuitpoint(const TThing* Thing, BinaryFunctor F)
{
    if((RegMode.LastExt)&&(Thing))
    {
        QVector<QPoint>::const_iterator i=Thing->IntCircuitPoints().begin();
        QVector<QPoint>::const_iterator end=Thing->IntCircuitPoints().end();
        while(i!=end)
        {
            F(i->x(), i->y());
            ++i;
        }
    }
    else
    {
        int sXmin=Thing->Xmin;
        for(qint64 y=Thing->Ymin;y<=Thing->Ymax;++y)
            for(int x=Thing->Xmax;x>=sXmin;--x)
            {
                pixrec p=ThingLayer(x,y);
                if(p.OnIntCircuit() && p.OnThing(Thing->id))
                    F(x,y);
            }
    }//else
    return F;
}

template<bool ThingPixel>
template<class TernaryFunctor>
TernaryFunctor TRecognizer<ThingPixel>::
for_each_intcircuitpoint_bits(const TThing* Thing, TernaryFunctor F)
{
    if((RegMode.LastExt)&&(Thing))
    {
        QVector<QPoint>::const_iterator i=Thing->IntCircuitPoints().begin();
        QVector<QPoint>::const_iterator end=Thing->IntCircuitPoints().end();
        while(i!=end)
        {
            pixrec p=ThingLayer(*i);
            F(i->x(), i->y(), p.bits);
            ++i;
        }
    }
    else
    {
        int sXmin=Thing->Xmin;
        for(qint64 y=Thing->Ymin;y<=Thing->Ymax;++y)
            for(int x=Thing->Xmax;x>=sXmin;--x)
            {
                pixrec p=ThingLayer(x,y);
                if(p.OnIntCircuit() && p.OnThing(Thing->id))
                    F(x,y,p.bits);
            }
    }//else
    return F;
}

template class Core::Recognizer::TRecognizer<true>;
//template class Core::Recognizer::TRecognizer<false>;
