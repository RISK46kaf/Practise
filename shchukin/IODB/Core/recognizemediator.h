#ifndef RECOGNIZEMEDIATOR_H
#define RECOGNIZEMEDIATOR_H

#include <QObject>
#include "Recognizer/trecognizer.h"
#include "morphdata.h"

namespace cv {
class Mat;
}

namespace Core {

enum CalcType
{
    Minimun = 0,
    Radius = 1,
    Fere = 2,
    All = 3
};

struct CalcError
{
    int code;
    QString mess;
};

class RecognizeMediator : public QObject
{
    Q_OBJECT
public:
    explicit RecognizeMediator(QObject *parent = 0);
    virtual ~RecognizeMediator();
    MorphData calculate(const QRect& area,const QPixmap& pix);
    void calculate(const QImage& img);
    MorphData calculate(const QRect& area,const QImage& img);
private:
    Recognizer::TRecognizer<true> *rec;
    Recognizer::TLayerB *bin;
    MorphData morphData;
private:
    inline void mat2Bin(cv::Mat *mat, Recognizer::TLayerB *bin);
    void thingsInfo(const Recognizer::TThingVector& things);
    inline cv::Mat qimage2CvMat(const QImage &inImage, bool inCloneImageData = true);
signals:
    void error(CalcError);
    void result(MorphData&);
public slots:
};

} // namespace Core
#endif // RECOGNIZEMEDIATOR_H
