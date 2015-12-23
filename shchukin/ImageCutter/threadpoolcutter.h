#ifndef THREADPOOLCUTTER_H
#define THREADPOOLCUTTER_H

#include <QObject>
#include <vips/vips8>

class QThreadPool;

class ThreadPoolCutter : public QObject
{
    Q_OBJECT
public:
    ThreadPoolCutter(const QString& filename,
                     int* tileSize,
                     int scalesCount,
                     const QString& outputDir,
                     QHash<int, QString*>* xmlHash,
                     QObject *parent = 0);
private:
    QThreadPool* _threadPool;
    vips::VImage _image;

signals:

public slots:
};

#endif // THREADPOOLCUTTER_H
