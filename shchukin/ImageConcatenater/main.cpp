#include <QCoreApplication>
#include <QtCore>
#include <vips/vips8>
#include <iostream>
#include <QTime>
#include <exception>
#include "myexception.h"
#include "threadpoolconcatenater.h"
#include "tilenameparser.h"

static const QString flagT = "-t"; // top left tile of group to concotinate
static const QString flagB = "-b"; // bottom right tile of group to concotinate
static const QString flagI = "-i"; // input directory /w tiles
static const QString flagO = "-o"; // output filename of concotinate image
static const QString flagBigF = "-F"; // format of inputed tiles names e.g. 'y=Yx=X.png'
static const QString flagA = "-a"; // format of inputed tiles names e.g. 'y=Yx=X.png'

inline void notNegativeIntegerCheck(const QString& src, int* dst, const QString& flagName)
{
    bool ok = false;
    *dst = src.toInt(&ok);
    if(!ok)
        throw MyException(
                QString("Assertion failed! There is NOT a integer next %1 flag\n")
                .arg(flagName).toStdString().c_str());
    else if(*dst < 0)
        throw MyException(
                QString("Assertion failed!"
                        " There is NEGATIVE integer next"
                        "%1 flag\n").arg(flagName).toStdString().c_str());
}

int main(int argc, char *argv[])
{
    QCoreApplication(argc,argv);
    qRegisterMetaType<QString>("QString");
    QTime myTimer;
    myTimer.start();
    if( VIPS_INIT( argv[0] ) )
        return( -1 );
    QStringList params;
    for(int i = 0; i < argc; ++i)
    {
        params << QString(argv[i]);
    }
    QString inputDirName;
    QString outputFilename;
    QString defOutPut("concotinated.png");
    QPoint topLeft(0,0);
    QPoint bottomRight(0,0);
    QString format = "y=Yx=X.png";
    bool a = false;
    try
    {
        if(params.contains(flagT) && params.indexOf(flagT) + 2 < params.count())
        {
            int x = -1;
            int y = -1;
            notNegativeIntegerCheck(params[params.indexOf(flagT) + 1],&x,
                    "first param of top left tile of group concotinate('-t'') ");
            notNegativeIntegerCheck(params[params.indexOf(flagT) + 2],&y,
                    "second param of top left tile of group to concotinate('-t'') ");
            topLeft.setX(x);
            topLeft.setY(y);
        }
        if(params.contains(flagB) && params.indexOf(flagB) + 2 < params.count())
        {
            int x = -1;
            int y = -1;
            notNegativeIntegerCheck(params[params.indexOf(flagB) + 1],&x,
                    "first param of bottom right tile of group to concotinate('-t'') ");
            notNegativeIntegerCheck(params[params.indexOf(flagB) + 2],&y,
                    "second param of bottom right tile of group to concotinate('-t'') ");
            bottomRight.setX(x);
            bottomRight.setY(y);
        }
        if(params.contains(flagI) && params.indexOf(flagI) + 1 < params.count())
        {
            inputDirName = (params[params.indexOf(flagI) + 1]);
            QDir dir(inputDirName);
            if(!dir.exists())
            {
                throw MyException(
                            "Assertion failed! "
                            "Input directory /w tiles next flag '-i' does NOT exist\n");
            }
            outputFilename = dir.path() +
                    "_(" + QString::number(topLeft.x()) + "," +
                    QString::number(topLeft.y()) + ")-(" +
                    QString::number(bottomRight.x()) + "," +
                    QString::number(bottomRight.y()) + ")" +
                    defOutPut;
        }
        if(params.contains(flagO) && params.indexOf(flagO) + 1 < params.count())
        {
            outputFilename = (params[params.indexOf(flagI) + 1]);
            QDir dir(outputFilename);
            if(!dir.exists())
            {
                throw MyException(
                            "Assertion failed! "
                            "Output directory next flag '-o' does NOT exist\n");
            }
        }
        if(params.contains(flagBigF) && params.indexOf(flagBigF) + 1 < params.count())
        {
            format = (params[params.indexOf(flagBigF) + 1]);
            bool ok =
                    (
                        format.lastIndexOf(".png") + 4  == format.size() ||
                        format.lastIndexOf(".jpg") + 4  == format.size() ||
                        format.lastIndexOf(".jpeg") + 5 == format.size() ||
                        format.lastIndexOf(".bmp") + 4  == format.size() ||
                        format.lastIndexOf(".*") + 2  == format.size()
                        ) &&
                    (
                        format.indexOf("X") != -1 && format.indexOf("Y") != -1
                    );
            if(!ok)
            {
                throw MyException(
                            "Assertion failed! "
                            "Format NOT correct!\n");
            }
        }
        if(params.contains(flagA))
        {
            a = true;
            QStringList filters;
            filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
            QDir dir(inputDirName);
            QFileInfoList fileInfoList =
                    dir.entryInfoList(filters, QDir::Files|QDir::NoDotAndDotDot);
            outputFilename = dir.path() +
                    "_all_tiles_" +
                    defOutPut;
            std::cout << "flag -a " << outputFilename.toStdString() << std::endl;
            QPair<QPoint, bool> tmp;
            QPoint z(0,0);
//            QRect rect(z,z);
            bottomRight = (z);
            std::cout << "fileInfoList" << fileInfoList.size() << std::endl;
            for(auto it = fileInfoList.begin(); it != fileInfoList.end(); ++it)
            {
                tmp = TileNameParser()(it->fileName(),format);
//                 if(!tmp.second) continue;
                bottomRight =(QPoint(
                         std::max(
                             bottomRight.x(),
                             tmp.first.x()),
                         std::max(
                             bottomRight.y(),
                             tmp.first.y())
                         )
                     );
            }
            std::cout << "rect " << bottomRight.x() << " " << bottomRight.y() << std::endl;
        }
        if(topLeft == bottomRight && !a)
        {
            throw MyException(
                        "Assertion failed! "
                        "Tiles group coordinates NOT set or NOT correct!\n");
        }
        if(inputDirName.isEmpty())
            throw MyException(
                    "Assertion failed! Input directory /w tiles NOT set\n");
        ThreadPoolConcatenater
                (inputDirName,outputFilename,topLeft,bottomRight,format);
        int ms = myTimer.elapsed();
        std::cout << "concotinated in "
                  << ms
                  << " ms or\n"
                  << (qreal)ms / 60000.0 << " mins or\n"
                  << (qreal)ms / 3600000.0 << " hours\n"
                  << "in " << outputFilename.toStdString() << std::endl;
    }
    catch(MyException& e)
    {
        std::cout << e.what() << std::endl;
        return -2;
    }
    return 0;
}

