#ifndef CONCATENATERRUNNABLE_H
#define CONCATENATERRUNNABLE_H
#include <QRunnable>
#include <vips/vips8>
#include <QtCore>
#include "tmpresult.h"

class ConcatenaterRunnable : public QRunnable
{
public:
    ConcatenaterRunnable(quint64 idx,
                         TmpResult* pTmpResult,
                         QStringList* tiles,
                         VipsDirection orientation = VIPS_DIRECTION_VERTICAL
                                  );
    virtual ~ConcatenaterRunnable();
    void run();
//https://github.com/jcupitt/libvips/issues/120
private:
    quint64                 _idx;
    TmpResult*              _result;
    QStringList*            _images;
    VipsDirection           _orient;
    QMutex                  _mutex;
    // собираю колонну и эмичу, когда все колонны проэмиченны в пулле
    // выстраивается очередь из колонн для окончательного слияния их в
};

#endif // CONCATENATERRUNNABLE_H
