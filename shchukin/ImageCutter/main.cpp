//#include <QCoreApplication>
#include <QtCore>
#include "threadpoolcutter.h"

#include <vips/vips8>
#include <QFile>
#include <QDir>
#include <QThreadPool>
#include <QTime>
#include <iostream>

static const QString flagF = "-f"; //set filename
static const QString flagS = "-s"; //set scales count
static const QString flagT = "-t"; //set tile size
static const QString flagO = "-o"; //set output directory
static const QString flagX = "-x"; //create xml mapping of cutted image

inline void positiveIntegerCheck(const QString& src, int* dst)
{
//    QMutex m;
    //m.lock();
    bool ok = false;
    *dst = src.toInt(&ok);
    if(!ok)
        throw "Assertion failed! There is NOT a integer next the scales count(\"-s\") flag\n";
    else if(*dst <= 0)
        throw "Assertion failed! There is NOT a positive integer next the scales count(\"-s\") flag\n";
    //m.unlock();
}

void inline writeFile( QHash<int, QString*>* xmlLines,
                       const QString &outputDir,
                       const QString &xmlOutput)
{
    QFile file(outputDir + "/" + xmlOutput + ".xml");
    file.open(QIODevice::ReadWrite);
    QTextStream stream( &file );
    stream << "<image>\n";
    for(int i = 1; i < xmlLines->count() + 1; ++i)
    {
        QString* tmp = xmlLines->operator [](i);
        stream << *tmp;
        delete tmp;
    }
    xmlLines->clear();
    stream << "</image>";
    file.close();
}

int main(int argc, char *argv[])
{
    QTime myTimer;
    myTimer.start();
    if( VIPS_INIT( argv[0] ) )
                    return( -1 );
    QHash<int, QString*>* xmlLineByValueId = new QHash<int, QString*>;

    QStringList params;
    for(int i = 0; i < argc; ++i)
    {
        params << QString(argv[i]);
    }
    QString filename = QString("%1/auto.jpg").arg(QDir::currentPath());
    int defaultScalesCount = 10;
    int scalesCount = defaultScalesCount;
    int tileSize[2] = {256,256};
    QString outputDir = QString(filename).replace(".","_");
    QString xmlOutput = "image";

    if(params.contains(flagF) && params.indexOf(flagF) + 1 < params.count())
    {
        filename = (params[params.indexOf(flagF) + 1]);
        outputDir = QString(filename).replace(".","_");
    }
    if(params.contains(flagS) && params.indexOf(flagS) + 1 < params.count())
    {
        positiveIntegerCheck(params[params.indexOf(flagS) + 1],&scalesCount);
    }
    if(params.contains(flagT) && params.indexOf(flagT) + 2 < params.count())
    {
        positiveIntegerCheck(params[params.indexOf(flagT) + 1],tileSize);
        positiveIntegerCheck(params[params.indexOf(flagT) + 2],tileSize + 1);
    }
    if(params.contains(flagO) && params.indexOf(flagO) + 1 < params.count())
    {
        QString tmp = params[params.indexOf(flagO) + 1];
        if(tmp.endsWith("/") && 1 < tmp.size())
            outputDir = tmp.remove(tmp.size() - 1,1);
        QDir dir(outputDir);
        if(!dir.exists())
            dir.mkpath(".");
    }
    if(params.contains(flagX) && params.indexOf(flagX) + 1 < params.count())
    {
        xmlOutput = params[params.indexOf(flagX) + 1].replace(".","_");
    }

    ThreadPoolCutter(filename,tileSize,scalesCount,outputDir,xmlLineByValueId);

    writeFile(xmlLineByValueId,outputDir,xmlOutput);
    int ms = myTimer.elapsed();
    std::cout << "cuted in "
              << ms
              << " ms or\n"
              << (qreal)ms / 60000.0 << "mins or\n"
              << (qreal)ms / 3600000.0 << "hours\n"
              << std::endl;
    std::cout << "la" << argv[0];
    delete xmlLineByValueId;
    return 0;
}
