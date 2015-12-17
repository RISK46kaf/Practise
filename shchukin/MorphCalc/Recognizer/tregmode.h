#ifndef TREGMODE_H
#define TREGMODE_H

#include <QtCore>

namespace Recognizer {

//вспомогательный класс для TRecognizer
//правила регистрирования точек в векторах
class TRegMode
{
    // template<pixB ThingPixel, TCoordSystemYDirection YDirection>
    template<bool ThingPixel>
    friend class TRecognizer;
    bool last_all;
    bool last_extunique;
    bool last_ext;
    bool last_intunique;
    bool last_int;
public:
    bool All;
    bool ExtUnique;
    bool Ext;
    bool IntUnique;
    bool Int;

    const bool& LastAll;
    const bool& LastExtUnique;
    const bool& LastExt;
    const bool& LastIntUnique;
    const bool& LastInt;

private:
    TRegMode();
    TRegMode(const TRegMode& RM);
    TRegMode& operator=(const TRegMode& RM);
    void SetLast();
};

}
#endif // TREGMODE_H
