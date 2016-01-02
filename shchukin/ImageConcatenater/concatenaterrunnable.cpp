#include "concatenaterrunnable.h"
#include <QVector>
#include <iostream>
#include <string>

ConcatenaterRunnable::ConcatenaterRunnable(quint64 idx,
                                           QMap<quint64, QString>& tiles,
                                           VipsDirection orientation, QObject *parent) :
    QObject(parent),
    _idx(idx), _images(tiles), _orient(orientation)
{
}

ConcatenaterRunnable::~ConcatenaterRunnable()
{
}

void ConcatenaterRunnable::run()
{
    VipsImage *accumulate;
    QString orient, corr1, corr2, tmpRes;
    auto it = _images.begin();
    QFileInfo fi(*it);
    corr1 = fi.fileName();
    if(!(accumulate =
         vips_image_new_from_file(
             (it)->toStdString().c_str(),
             "access",
             VIPS_ACCESS_SEQUENTIAL,
             NULL )))
    {
        vips_error_exit( NULL );
    }
    if(_orient == VIPS_DIRECTION_VERTICAL)
        orient = "c";
    else if(_orient == VIPS_DIRECTION_HORIZONTAL)
        orient = "r";
    ++it;
    for(; it != _images.end(); ++it)
    {
        fi = QFileInfo(*it);
        corr2 = fi.fileName();
        VipsImage *x;
        VipsImage *y;
        if(!(x =
             vips_image_new_from_file(
                 (it)->toStdString().c_str(),
                 "access", VIPS_ACCESS_SEQUENTIAL,
                 NULL )))
        {
            vips_error_exit( NULL );
        }
        if( vips_join( accumulate, x, &y,
                       _orient, NULL ) )
            vips_error_exit( NULL );
        g_object_unref( x );
        g_object_unref( accumulate );
        accumulate = y;
    }
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
    emit tmpResult({1,_idx,tmpRes});
}
