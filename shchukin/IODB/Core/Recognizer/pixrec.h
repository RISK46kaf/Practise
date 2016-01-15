#ifndef PIXREC
#define PIXREC

#include <QtCore>

namespace Core {
namespace Recognizer {

struct pixrec
{
    qint64 id;
    qint16 bits;

    void zero(){id=0; bits=0;}

    pixrec(){ zero(); }
    pixrec(qint64 ID, qint16 Bits) : id(ID), bits(Bits) {}

    void SetThing(qint64 nid){bits|=0x8000; id=nid;}

    //принадлежит ли пиксель какому-либо объекту
    bool OnThing()const{return bits & 0x8000;}

    //принадлежит ли пиксель объекту nid
    bool OnThing(qint64 nid)const
    {
        return (id==nid)&&(bits & 0x8000);
    }

    //принадлежит ли пиксель фону
    bool OnBack()const{return !OnThing();}

    //принадлежит ли пиксель внешней границе какого либо объекта
    bool OnExtCircuit()const{return (bits&0x9000)==0x9000;}

    //принадлежит ли пиксель внутренней границе какого либо объекта
    bool OnIntCircuit()const{return (bits&0xA000)==0xA000;}

    //принадлежит ли пиксель правой границе (внешней или внутренней) объекта nid
    bool OnRightCircuit(qint64 nid)const{return OnThing(nid)&&(bits&0x0022);}

    //принадлежит ли пиксель краю
    bool OnEdge()const{return bits&0x4000;}

};

} // namespace Recognizer
} // namespace Core
#endif // PIXREC

