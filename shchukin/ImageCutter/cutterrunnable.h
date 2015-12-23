#ifndef CUTTERRUNNABLE_H
#define CUTTERRUNNABLE_H

#include <QRunnable>
#include <QtCore>

namespace vips {
class VImage;
}

class CutterRunnable : public QRunnable
{
public:
    CutterRunnable(vips::VImage& image,
                   int scaleIndex,
                   int* tileSize,
                   int scalesCount,
                   const QString& outputDir,
                   QHash<int, QString*> *xmlHash);
    void run();
private:
    void insertLineToXmlHash(int value,
                      int width,
                      int height,
                      int tile_amount_w,
                      int tile_amount_h) const;
    void imageScales(vips::VImage& image,/*const QString& filename,*/
                     int i, int scalesCount,
                     int* tileSize,
                     const QString& outputDir);

private:
    vips::VImage&               _image;
    int                         _scaleIdx;
    int*                        _tileSize;
    int                         _scalesCount;
    QString                     _outputDir;
    QHash<int, QString*>*        _xmlHash;
};

#endif // CUTTERRUNNABLE_H
