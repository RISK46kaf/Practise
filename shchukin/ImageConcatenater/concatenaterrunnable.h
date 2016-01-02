#ifndef CONCATENATERRUNNABLE_H
#define CONCATENATERRUNNABLE_H
#include <QRunnable>
#include <QObject>
#include <QtCore>
#include <vips/vips8>
#include "tmpresult.h"

class ConcatenaterRunnable : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ConcatenaterRunnable(quint64 idx,
                         QMap<quint64, QString> &tiles,
                         VipsDirection orientation = VIPS_DIRECTION_VERTICAL,
                         QObject* parent = 0
                                  );
    virtual ~ConcatenaterRunnable();

protected:
    void run();

signals:
    void tmpResult(TmpResult);
//    void quit();
//https://github.com/jcupitt/libvips/issues/120
private:
    quint64                 _idx;
    QMap<quint64, QString >
                            _images;
    VipsDirection           _orient;
//    QMutex                  _mutex;
    // собираю колонну и эмичу, когда все колонны проэмиченны в пулле
    // выстраивается очередь из колонн для окончательного слияния их в
};

#endif // CONCATENATERRUNNABLE_H
