#include "cutterrunnable.h"
#include <iostream>
#include <fstream>
#include <vips/vips8>
#include <QDir>
#include <QDebug>
#include <QHash>

CutterRunnable::CutterRunnable(vips::VImage& image,
                               int scaleIndex,
                               int* tileSize,
                               int scalesCount,
                               const QString& outputDir,
                               QHash<int, QString *> *xmlHash) :
    _image(image), _scaleIdx(scaleIndex), _tileSize(tileSize),
    _scalesCount(scalesCount), _outputDir(outputDir), _xmlHash(xmlHash)
{
}

void CutterRunnable::run()
{
    imageScales(_image,_scaleIdx,_scalesCount,_tileSize,_outputDir);
}

inline void CutterRunnable::insertLineToXmlHash(int value,
                                                int width,
                                                int height,
                                                int tile_amount_w,
                                                int tile_amount_h) const
{
//    QMutex m;
    //m.lock();
     _xmlHash->insert(value,
                      new QString("\t<scale value=\"" +
                       QString::number(value) + "\" width=\"" +
                       QString::number(width) + "\" height=\"" +
                       QString::number(height) + "\" tile_amount_w=\"" +
                       QString::number(tile_amount_w) + "\" tile_amount_h=\"" +
                       QString::number(tile_amount_h) + "\"/>\n"));
    //m.unlock();
}

void CutterRunnable::imageScales(vips::VImage& image,
                                 int i,
                                 int scalesCount,
                                 int *tileSize,
                                 const QString &outputDir)
{
//    QMutex m;
    //m.lock();
//    vips::VImage image = vips::VImage::new_from_file(filename.toStdString().c_str());
    //m.unlock();
    double sc = 1.0 / (double)i;
    //m.lock();
    vips::VImage scaled_image = image.similarity( vips::VImage::option()->set( "scale", sc ) );
    //m.unlock();
    int tile_amount_w = scaled_image.width() / tileSize[0] + 1;
    int tile_amount_h = scaled_image.height() / tileSize[1] + 1;
    insertLineToXmlHash(i,scaled_image.width(),scaled_image.height(),tile_amount_w,tile_amount_h);
    int shift_x = 0;
    int shift_y = 0;
    int last_pixel_x = 0;
    int last_pixel_y = 0;
    QString dirName = outputDir;
    QString previewDir = dirName + "/Preview";
    QString originDir = dirName + "/Morph";
    dirName = dirName + "/1_" + QString::number(i);
    QDir dir(dirName);
    //m.lock();
    if(!dir.exists())
        dir.mkpath(".");
    dir = QDir(previewDir);
    if(!dir.exists())
        dir.mkpath(".");
    dir = QDir(originDir);
    if(!dir.exists())
        dir.mkpath(".");
    //m.unlock();
    QString pathP =
            previewDir + "/1_" + QString::number(i*5) + ".jpg[Q=35,optimize_coding]";
    QString pathO =
            originDir + "/morph.png[compression=9]";
    for(int h = 0; h < tile_amount_h; ++h)
    {
        last_pixel_y = tileSize[1];
        //m.lock();
        if(h == (tile_amount_h-1))
            last_pixel_y = scaled_image.height() - ((tile_amount_h-1) * tileSize[1]);
        //m.unlock();
        for(int w = 0; w < tile_amount_w; ++w)
        {
            last_pixel_x = tileSize[0];
            //m.lock();
            if(w == (tile_amount_w - 1))
                last_pixel_x = scaled_image.width() - (tile_amount_w - 1) * tileSize[0];
            if(last_pixel_x <= 0 || last_pixel_y <= 0)
            {
                shift_x+= tileSize[0];
                //m.unlock();
                continue;
            }
            //m.unlock();
            QString path1 = (dirName+"/"+"y=" + QString::number(h)+"x=" + QString::number(w)+".jpg[Q=35,optimize_coding]");
            //m.lock();
            std::cout << path1.toStdString().c_str() << std::endl;

            if(scaled_image.width() <= (shift_x + last_pixel_x)
                   && scaled_image.height() > (shift_y + last_pixel_y))
            {
                vips::VImage tile = scaled_image.extract_area
                        (shift_x,shift_y,scaled_image.width() - shift_x, last_pixel_y);
//                std::cout << "path to save" << path1.toStdString().c_str() << std::endl;
                tile.write_to_file(path1.toStdString().c_str());
            }
            else if(scaled_image.width() > (shift_x + last_pixel_x) and scaled_image.height() <= (shift_y + last_pixel_y))
            {
                vips::VImage tile = scaled_image.extract_area
                        (shift_x,shift_y,last_pixel_x, scaled_image.height() - shift_y);
//                std::cout << "path to save" << path1.toStdString().c_str() << std::endl;
                tile.write_to_file(path1.toStdString().c_str());
            }
            else if(scaled_image.width() <= (shift_x + last_pixel_x) and scaled_image.height() <= (shift_y + last_pixel_y))
            {
                vips::VImage tile = scaled_image.extract_area
                        (shift_x,shift_y,scaled_image.width() - shift_x, scaled_image.height() - shift_y);
//                std::cout << "path to save" << path1.toStdString().c_str() << std::endl;
                tile.write_to_file(path1.toStdString().c_str());
            }
            else
            {
                vips::VImage tile = scaled_image.extract_area
                        (shift_x,shift_y,last_pixel_x, last_pixel_y);
//                std::cout << "path to save" << path1.toStdString().c_str() << std::endl;
                tile.write_to_file(path1.toStdString().c_str());
            }
            //m.unlock();
            shift_x+= tileSize[0];
        }
        shift_y= shift_y + tileSize[1];
        shift_x = 0;
    }
    //m.lock();
    if(i == scalesCount)
    {
//        std::cout << "path to save" << path.toStdString().c_str() << std::endl;
        vips::VImage image = scaled_image.similarity( vips::VImage::option()->set( "scale", 0.2 ) );
        image.write_to_file(pathP.toStdString().c_str());
    }
    if(i == 10)
    {
        scaled_image.write_to_file(pathO.toStdString().c_str());
    }
    //m.unlock();
}
