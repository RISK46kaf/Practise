#include "threadpoolconcatenater.h"
#include "tilenameparser.h"
#include "concatenaterrunnable.h"
#include <QThreadPool>
#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <iostream>
#include <QFile>

ThreadPoolConcatenater::ThreadPoolConcatenater(const QString &inputDirName,
                                               const QString &outputFilename,
                                               const QPoint &topLeft,
                                               const QPoint &bottomRight,
                                               const QString &format,
                                               QObject *parent) :
    QObject(parent),_i(inputDirName), _o(outputFilename),
    _t(topLeft), _b(bottomRight), _F(format), _threadPool(new QThreadPool(this)),
    _done(0), _tmp({0,0,""}), _deleteLater(NULL)
{
    init();
    calculation();
    if(_done)
    {
        while(!QFile::copy(QFileInfo(_tmp.path).absoluteFilePath(),
                           QFileInfo(_o).absoluteFilePath()))
        {
            QFile::remove(QFileInfo(_o).absoluteFilePath());
        }
        clearTmpFolder();
    }
}

ThreadPoolConcatenater::~ThreadPoolConcatenater()
{
    if(_deleteLater)
    {
        qDeleteAll(*_deleteLater);
        delete _deleteLater;
    }
}

void ThreadPoolConcatenater::init()
{
    clearTmpFolder();
    QDir tmpDir(QFileInfo(QDir::tempPath()
                       + "/ImageConcatenater/").absolutePath());
    if(!tmpDir.exists())
        tmpDir.mkpath(".");
    int maxThreadsCount = QThread::idealThreadCount();
    maxThreadsCount = 1;// maxThreadsCount < 1 ? 2 : maxThreadsCount;
    _threadPool->setMaxThreadCount(maxThreadsCount);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
    QDir dir(_i);
    QFileInfoList fileInfoList =
            dir.entryInfoList(filters, QDir::Files|QDir::NoDotAndDotDot);
    QPair<QPoint, bool> tmp;
    QPoint z(0,0);
    QRect rect(_t,_b);
    _images.resize(QRect(z,_b).size());
    if(fileInfoList.size() == 1)
    {
        auto it = fileInfoList.begin();
        tmp = TileNameParser()(it->fileName(),_F);
        if(tmp.second && rect.contains(tmp.first))
        {
            QFile::copy(
                        it->absoluteFilePath(),
                        QFileInfo(_o).absoluteFilePath()
                        );
            _done = true;
            return;
        }
    }
    for(auto it = fileInfoList.begin(); it != fileInfoList.end(); ++it)
    {
        tmp = TileNameParser()(it->fileName(),_F);
        if(tmp.second && rect.contains(tmp.first))
        {
            _images(tmp.first) =
                    it->absoluteFilePath();
            std::cout << QTime::currentTime().toString().toStdString()
                      << " "
                      << it->absoluteFilePath().toStdString()
                      << " add to concatenate"
                      << std::endl;
        }
    }
    // если файл только один не начинаем!
    std::cout << QTime::currentTime().toString().toStdString()
              << "result size " << _images.size().width() << " rows "
              << _images.size().height() << " cols of tiles" << std::endl;
    _tmpResults.resize(_images.width());
    _deleteLater = new QVector<QStringList*>;
}

void ThreadPoolConcatenater::calculation()
{
    quint64 idx = 0;
    if(!_done)
    {
        ConcatenaterRunnable* runnable;
        for(quint64 x = 0; x < _images.width(); ++x)
        {
            _mutex.lock();
            if(_tmp.isValid && QFileInfo(_tmp.path).exists())
            {
                std::cout << QTime::currentTime().toString().toStdString()
                          << " tmp idx " << _tmp.idx << std::endl;
                _tmpResults[_tmp.idx] = _tmp.path;
                std::cout << QTime::currentTime().toString().toStdString()
                          << " path " << _tmp.path.toStdString() << std::endl;
                _tmp = {0,0,""};
            }
            QStringList* sl = new QStringList(_images.col(x).toList());
            for(int i = 0; i < sl->size(); ++ i)
            {
                if((*sl)[i].isEmpty() || !QFileInfo((*sl)[i]).exists())
                    sl->removeAt(i);
            }
            runnable = new ConcatenaterRunnable(x,&_tmp, sl);
            _images.col(x).clear();
            _deleteLater->push_back(sl);
//            std::cout << QTime::currentTime().toString().toStdString()
//                      << " task to concatenate " << x << " col started"
//                      << std::endl;
            _mutex.unlock();
            _threadPool->start(runnable);
        }
        while(true)
        {
            _mutex.lock();
            if(_tmp.isValid && QFileInfo(_tmp.path).exists())//if(_tmp.isValid)
            {
                std::cout << QTime::currentTime().toString().toStdString()
                          << " tmp idx " << _tmp.idx << std::endl;
                _tmpResults[_tmp.idx] = _tmp.path;
                std::cout << QTime::currentTime().toString().toStdString()
                          << " path" << _tmp.path.toStdString() << std::endl;
                _tmp = {0,0,""};
            } else if(!_threadPool->activeThreadCount())
            {
                QStringList* sl = new QStringList();
                for(int i = 0; i < _tmpResults.size(); ++i )
                {
                    sl->push_back(_tmpResults[i]);
                }
                _tmpResults.clear();
                _deleteLater->push_back(sl);
                runnable =
                        new ConcatenaterRunnable(
                            idx,
                            &_tmp,
                            sl,
                            VIPS_DIRECTION_HORIZONTAL
                            );
                std::cout << QTime::currentTime().toString().toStdString()
                          << " task to concatenate " << " cols to row started"
                          << std::endl;
                std::cout << sl->size() <<" sl size\n";
                _threadPool->start(runnable);
                _mutex.unlock();
                break;
            }
            _mutex.unlock();
        }
        while(true)
        {
            _mutex.lock();
            if(!_threadPool->activeThreadCount())
            {
                if(_tmp.isValid)
                    _done = true;
                std::cout << "path" << _tmp.path.toStdString() << std::endl;
                _mutex.unlock();
                break;
            }
            _mutex.unlock();
        }
    }
}

void ThreadPoolConcatenater::clearTmpFolder()
{
    QDir tmpDir(QFileInfo(QDir::tempPath()
                       + "/ImageConcatenater/").absolutePath());
    tmpDir.setNameFilters(QStringList() << "*.*");
    tmpDir.setFilter(QDir::Files);
    foreach(QString dirFile, tmpDir.entryList())
    {
        tmpDir.remove(dirFile);
    }
}
