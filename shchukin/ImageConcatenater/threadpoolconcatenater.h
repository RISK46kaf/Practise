#ifndef THREADPOOLCONCATENATER_H
#define THREADPOOLCONCATENATER_H

#include <QObject>
#include <QtCore>
#include <QPoint>
#include <vips/vips8>
#include "tmatrixt.h"
#include "tmpresult.h"

class QThreadPool;

class ThreadPoolConcatenater : public QObject
{
    Q_OBJECT
public:
    explicit ThreadPoolConcatenater(const QString& inputDirName,
                                    const QString& outputFilename,
                                    const QPoint& topLeft,
                                    const QPoint& bottomRight,
                                    const QString& format,
                                    QObject *parent = 0);
    ~ThreadPoolConcatenater();
signals:

public slots:
private:
    void init();
    void calculation();
    void clearTmpFolder();
//    void lookForTmpResult(quint64 idx, quint64 size);
private:
    QString                     _i;
    QString                     _o;
    QPoint                      _t;
    QPoint                      _b;
    QString                     _F;
    QThreadPool*                _threadPool;
    TMatrixT<QString>           _images;
    QVector<QString>            _tmpResults;
//    QStringList                 _results;
    bool                        _done;
    QMutex                      _mutex;
    TmpResult                   _tmp;
    QVector<QStringList*>*      _deleteLater;
};

#endif // THREADPOOLCONCATENATER_H
