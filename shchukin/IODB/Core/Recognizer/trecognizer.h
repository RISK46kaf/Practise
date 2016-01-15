#ifndef TRECOGNIZER_H
#define TRECOGNIZER_H

#include <QtCore>
#include "tthing.h"
#include "tregmode.h"
#include "treservationrules.h"
#include "tlayerb.h"
#include "tlayerrec.h"

namespace Core {
namespace Recognizer {

typedef QVector<TThing*> TThingVector;

template<bool ThingPixel>
class TRecognizer
{
  struct TPimpl;
  TPimpl* pimpl;

  //распознавание объектов цвета ThingPixel

  enum TDirection { dWest = 0, dNorth = 1, dEast = 2, dSouth = 3 };
  //абсолютное направление движения при обходе частиц
  void TurnLeft(TDirection& d) // поворот налево относительно текущего направления
  {  d = static_cast<TDirection>((d+3) % 4); }

  void TurnRight(TDirection& d) // поворот налево относительно текущего направления
  {  d = static_cast<TDirection>((d+1) % 4); }

  void FindCircuit(const TLayerB& src, qint64 StartX, qint64 StartY,
                   TThing* Thing, qint64 ThingNumber, bool External);
  //найти границу очередной частицы и поместить данные о ней
  //в thing_layer и в Thing

  void FindEntry(const TLayerB& src);
  //найти внутренности частицы, информация о границе которой хранится
  //в последнем объекте леера


 public:
  static const bool thing_pixel = ThingPixel;
//  static const TCoordSystemYDirection y_direction=YDirection;

  TRegMode RegMode;                   //режим регистрации точек объекта
  TReservationRules ReservationRules; //правила резервирования памяти под точки объекта

  TRecognizer();
  TRecognizer(const TRecognizer& R);
  TRecognizer& operator=(const TRecognizer& R);
  ~TRecognizer();

  const TLayerRec& ThingLayer()const;
  TThingVector ThingVector()const;

  void Clear(bool lay=false, bool vec=false);
  void Reserve(qint64 things_count);
  void Unreserve();
  void FindThings(const TLayerB& src);
  void CalculateRadius();
  void CalculateFere();
  void ClearRegPoints(bool All=true, bool Ext=true, bool Int=true);

  const TThing& GetThing(qint64 x, qint64 y)const;
  template<class TXPoint>
  const TThing& GetThing(const TXPoint& P)const{return GetThing(P.X,P.Y);}

  template<class BinaryFunctor>
  BinaryFunctor for_each_point(const TThing* Thing, BinaryFunctor F);
  template<class TernaryFunctor>
  TernaryFunctor for_each_point_bits(const TThing* Thing, TernaryFunctor F);

  template<class BinaryFunctor>
  BinaryFunctor for_each_extcircuitpoint(const TThing* Thing, BinaryFunctor F);
  template<class TernaryFunctor>
  TernaryFunctor for_each_extcircuitpoint_bits(const TThing* Thing, TernaryFunctor F);

  template<class BinaryFunctor>
  BinaryFunctor for_each_intcircuitpoint(const TThing* Thing, BinaryFunctor F);
  template<class TernaryFunctor>
  TernaryFunctor for_each_intcircuitpoint_bits(const TThing* Thing, TernaryFunctor F);

  bool SelfTest(); //это метод самотестирования
};

} // namespace Recognizer
} // namespace Core
#endif // TRECOGNIZER_H
