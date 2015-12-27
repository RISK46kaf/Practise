#include "concatenaterrunnable.h"
#include <QVector>
#include <QtCore>
#include <iostream>
#include <string>


ConcatenaterRunnable::ConcatenaterRunnable(quint64 idx,
                                           TmpResult *pTmpResult,
                                           QStringList *tiles,
                                           VipsDirection orientation) :
    _idx(idx), _result(pTmpResult), _images(tiles), _orient(orientation)
{
//    QMutex m;
//    m.lock();
//    _images->swap(tiles);
//    for(int i = 0; i < _images->size(); ++ i)
//    {
//        if(_images[i].isEmpty() || !QFileInfo(_images[i]).exists())
//            _images->removeAt(i);
//    }
//    m.unlock();
}

ConcatenaterRunnable::~ConcatenaterRunnable()
{
}

void ConcatenaterRunnable::run()
{
    std::cout << "ConcatenaterRunnable::run()\n";
//    QMutex m;
    VipsImage *accumulate;
    QString orient, corr1, corr2, tmpRes;
//    m.lock();
    if(!_images && !_images->size())
    {
//        m.unlock();
        return;
    }
//    m.unlock();
    auto it = _images->begin();
    QFileInfo fi(*it);
    corr1 = fi.fileName();
//    m.lock();
    if(!(accumulate =
         vips_image_new_from_file(
             (it)->toStdString().c_str(),
             "access",
             VIPS_ACCESS_RANDOM,
             NULL )))
    {
//        m.unlock();
        vips_error_exit( NULL );
    }
//    m.unlock();
    if(_orient == VIPS_DIRECTION_VERTICAL)
        orient = "c";
    else if(_orient == VIPS_DIRECTION_HORIZONTAL)
        orient = "r";
    ++it;
    for(; it != _images->end(); ++it)
    {
//        m.lock();
        fi = QFileInfo(*it);
        corr2 = fi.fileName();
        VipsImage *x;
        VipsImage *y;
        if(!(x =
             vips_image_new_from_file(
                 (it)->toStdString().c_str(),
                 "access", VIPS_ACCESS_RANDOM,
                 NULL )))
        {
//            m.unlock();
            vips_error_exit( NULL );
        }
//        m.unlock();
        if( vips_join( accumulate, x, &y,
                       _orient, NULL ) )
            vips_error_exit( NULL );
        g_object_unref( x );
        g_object_unref( accumulate );
        accumulate = y;
    }
//    m.lock();
    tmpRes = (QDir::tempPath() + "/ImageConcatenater/" + orient + "_"
              + QString::number(_idx)
              + ".png"
              );
    if( vips_image_write_to_file(
                accumulate,
                tmpRes.toStdString().c_str(),
                NULL
                )
            )
        vips_error_exit( NULL );
    g_object_unref( accumulate );
    std::cout << "_idx " << _idx << " " << std::endl;
    *_result = TmpResult{1,_idx,tmpRes};
//    m.unlock();
}
