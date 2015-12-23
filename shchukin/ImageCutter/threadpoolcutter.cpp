#include "threadpoolcutter.h"
#include "cutterrunnable.h"
#include <QThreadPool>

ThreadPoolCutter::ThreadPoolCutter(const QString &filename,
                                   int *tileSize,
                                   int scalesCount,
                                   const QString &outputDir,
                                   QHash<int, QString *> *xmlHash,
                                   QObject *parent)
    : QObject(parent), _threadPool(new QThreadPool(this))
{
    int maxThreadsCount = QThread::idealThreadCount();
    maxThreadsCount = maxThreadsCount < 1 ? 2 : maxThreadsCount;
    _threadPool->setMaxThreadCount(maxThreadsCount);
    _image = vips::VImage::new_from_file(filename.toStdString().c_str());
    for(int i = 1; i < scalesCount + 1; ++i)
    {
        CutterRunnable* runnable = new CutterRunnable(_image,i,tileSize,scalesCount,outputDir,xmlHash);
        _threadPool->start(runnable);
    }
}
