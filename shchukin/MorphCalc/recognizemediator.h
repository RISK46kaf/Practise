#ifndef RECOGNIZEMEDIATOR_H
#define RECOGNIZEMEDIATOR_H

#include <QObject>
#include "Recognizer/trecognizer.h"

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

namespace cv {
class Mat;
}

class RecognizeMediator : public QObject
{
    Q_OBJECT
public:
    explicit RecognizeMediator(QObject *parent = 0);
    virtual ~RecognizeMediator();
    void calculate(const QRect& area,const QPixmap& pix);
    void calculate(const QImage& img);
    void calculate(const QRect& area,const QImage& img);
private:
    Recognizer::TRecognizer<true> *rec;
    Recognizer::TLayerB *bin;
private:
    inline void mat2Bin(cv::Mat *mat, Recognizer::TLayerB *bin);
    void thingsInfo(const Recognizer::TThingVector& things);
    inline cv::Mat qimage2CvMat(const QImage &inImage, bool inCloneImageData = true);
signals:
    void error(CalcError);
    void result(QString);
public slots:
};

#endif // RECOGNIZEMEDIATOR_H
