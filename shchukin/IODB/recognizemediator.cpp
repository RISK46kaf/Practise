#include <QPixmap>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "recognizemediator.h"
#ifdef _DEBUG
#include <QDebug>
#endif
using namespace Recognizer;

RecognizeMediator::RecognizeMediator(QObject *parent) : QObject(parent)
{
    rec = 0;
    bin = 0;
#ifdef _DEBUG
    qDebug("RecognizeMediator::RecognizeMediator()");
#endif
}

RecognizeMediator::~RecognizeMediator()
{
    if(rec)
        delete rec;
    if(bin)
        delete bin;
}

MorphData RecognizeMediator::calculate(const QRect &area, const QPixmap &pix)
{
    if((pix.width() < area.width()) ||
            (pix.height() < area.height()))
    {
        //TODO emit some error mess
        return MorphData();
    }
    QImage img = pix.copy(area).toImage();
    calculate(img);
    return morphData;
}

void RecognizeMediator::calculate(const QImage &img)
{
    cv::Mat mat = qimage2CvMat(img);
    if(rec)
        delete rec;
    if(bin)
        delete bin;
    rec = new TRecognizer<true>();
    bin = new TLayerB(mat.cols,mat.rows);

    mat2Bin(&mat,bin);
    rec->FindThings(*bin);
    rec->CalculateRadius();
    rec->CalculateFere();
    thingsInfo(rec->ThingVector());
}

MorphData RecognizeMediator::calculate(const QRect &area, const QImage &img)
{
    if(!img.width() || !img.height())
    {
        //TODO emit some error mess
        return MorphData();
    }
    QImage image = img.copy(area);
    calculate(image);
    return morphData;
}

inline cv::Mat RecognizeMediator::qimage2CvMat(const QImage &inImage, bool inCloneImageData)
{
    switch ( inImage.format() )
    {
    // 8-bit, 4 channel
    case QImage::Format_RGB32:
    {
        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

        return (inCloneImageData ? mat.clone() : mat);
    }

    // 8-bit, 3 channel
    case QImage::Format_RGB888:
    {
        if ( !inCloneImageData )
            qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";

        QImage   swapped = inImage.rgbSwapped();

        return cv::Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
    }

    // 8-bit, 1 channel
    case QImage::Format_Indexed8:
    {
        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

        return (inCloneImageData ? mat.clone() : mat);
    }

    default:
        qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
        break;
    }

    return cv::Mat();
}

void RecognizeMediator::mat2Bin(cv::Mat *mat, Recognizer::TLayerB* bin)
{
    cv::cvtColor(*mat, *mat, cv::COLOR_BGR2GRAY);
    cv::medianBlur(*mat,*mat,5);
//    cv::threshold(*mat, *mat, 180, 255, CV_THRESH_BINARY);
    cv::threshold(*mat, *mat, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    for(int y = 0; y < mat->rows; ++y)
    {
        const uchar* p = mat->ptr<uchar>(y);
        for(int x = 0; x < mat->cols; ++x)
        {
            bin->Pixel(x,y) = p[x]!=0;
        }
    }
#ifdef _DEBUG
    qDebug("mat2Bin ends");
#endif
}

void RecognizeMediator::thingsInfo(const Recognizer::TThingVector &things)
{
//#ifdef _DEBUG
    qDebug("thingsInfo");
//#endif
    QString thingsText;
    qint64 maxSquare = 0;
    MorphData data;
    int i = 1;
    for(auto j = 1; j < things.size(); ++j)
    {
        if(maxSquare < things[j]->Square)
        {
            maxSquare = things[j]->Square;
            i = j;
        }
    }
    if(maxSquare)
    {
        thingsText.append(QString("id: %1; ")
                          .arg(QString::number(things[i]->id)));
        thingsText.append(QString("Xmin: %1; ")
                          .arg(QString::number(things[i]->Xmin)));
        thingsText.append(QString("Ymin: %1; ")
                          .arg(QString::number(things[i]->Ymin)));
        thingsText.append(QString("Xmax: %1; ")
                          .arg(QString::number(things[i]->Xmax)));
        thingsText.append(QString("Ymax: %1; ")
                          .arg(QString::number(things[i]->Ymax)));
        thingsText.append(QString("Spots: %1; ")
                          .arg(QString::number(things[i]->Spots)));
        data.Spots = things[i]->Spots;
        thingsText.append(QString("SpotsSquare: %1; ")
                          .arg(QString::number(things[i]->SpotsSquare)));
        data.SpotsSquare = things[i]->SpotsSquare;
        thingsText.append(QString("Start: (%1,%2); ")
                          .arg(QString::number(things[i]->Start.x()))
                          .arg(QString::number(things[i]->Start.y())));
        thingsText.append(QString("ExtCircuit8Len: %1; ")
                          .arg(QString::number(things[i]->ExtCircuit8Len)));
        data.ExtCircuit8Len = things[i]->ExtCircuit8Len;
        thingsText.append(QString("ExtCircuit4Len: %1; ")
                          .arg(QString::number(things[i]->ExtCircuit4Len)));
        data.ExtCircuit4Len = things[i]->ExtCircuit4Len;
        thingsText.append(QString("ExtPerimetr: %1; ")
                          .arg(QString::number(things[i]->ExtPerimetr)));
        data.ExtPerimetr = things[i]->ExtPerimetr;
        thingsText.append(QString("IntCircuit8Len: %1; ")
                          .arg(QString::number(things[i]->IntCircuit8Len)));
        data.IntCircuit8Len = things[i]->IntCircuit8Len;
        thingsText.append(QString("IntCircuit4Len: %1; ")
                          .arg(QString::number(things[i]->IntCircuit4Len)));
        data.IntCircuit4Len = things[i]->IntCircuit4Len;
        thingsText.append(QString("IntPerimetr: %1; ")
                          .arg(QString::number(things[i]->IntPerimetr)));
        data.IntPerimetr = things[i]->IntPerimetr;
        thingsText.append(QString("Square: %1; ")
                          .arg(QString::number(things[i]->Square)));
        data.Square = things[i]->Square;
        thingsText.append(QString("Fullness: %1; ")
                          .arg(QString::number(things[i]->Fullness)));
        data.Fullness = things[i]->Fullness;
        thingsText.append(QString("ShapeFactor: %1; ")
                          .arg(QString::number(things[i]->ShapeFactor)));
        data.ShapeFactor = things[i]->ShapeFactor;
        thingsText.append(QString("Center: (%1,%2); ")
                          .arg(QString::number(things[i]->Center.x()))
                          .arg(QString::number(things[i]->Center.y())));
        thingsText.append(QString("Radius MaxRadius: %1; ")
                          .arg(QString::number(things[i]->Radius.MaxRadius)));
        data.MaxRadius = things[i]->Radius.MaxRadius;
        thingsText.append(QString("Radius MinRadius: %1; ")
                          .arg(QString::number(things[i]->Radius.MinRadius)));
        data.MinRadius = things[i]->Radius.MinRadius;
        thingsText.append(QString("Radius AverageRadius: %1; ")
                          .arg(QString::number(things[i]->Radius.AverageRadius)));
        data.AverageRadius = things[i]->Radius.AverageRadius;
        thingsText.append(QString("Radius MeanSquareRadius: %1; ")
                          .arg(QString::number(things[i]->Radius.MeanSquareRadius)));
        data.MeanSquareRadius = things[i]->Radius.MeanSquareRadius;
        thingsText.append(QString("Radius MaxRadiusPoint: (%1,%2); ")
                          .arg(QString::number(things[i]->Radius.MaxRadiusPoint.x()))
                          .arg(QString::number(things[i]->Radius.MaxRadiusPoint.y())));
        thingsText.append(QString("Radius MinRadiusPoint: (%1,%2); ")
                          .arg(QString::number(things[i]->Radius.MinRadiusPoint.x()))
                          .arg(QString::number(things[i]->Radius.MinRadiusPoint.y())));
        thingsText.append(QString("Radius InertiaMoment: %1; ")
                          .arg(QString::number(things[i]->Radius.InertiaMoment)));
        data.InertiaMoment = things[i]->Radius.InertiaMoment;
        thingsText.append(QString("Radius RelInertiaMoment: %1; ")
                          .arg(QString::number(things[i]->Radius.RelInertiaMoment)));
        data.RelInertiaMoment = things[i]->Radius.RelInertiaMoment;
        thingsText.append(QString("Radius Valid: %1; ")
                          .arg(QString::number(things[i]->Radius.Valid)));
        data.RadValid = things[i]->Radius.Valid;
        thingsText.append(QString("Fere MinDiametr: %1; ")
                          .arg(QString::number(things[i]->Fere.MinDiametr)));
        data.MinDiametr = things[i]->Fere.MinDiametr;
        thingsText.append(QString("Fere AngleMin: %1; ")
                          .arg(QString::number(things[i]->Fere.AngleMin)));
        data.AngleMin = things[i]->Fere.AngleMin;
        thingsText.append(QString("Fere CoupleMin1: (%1,%2); ")
                          .arg(QString::number(things[i]->Fere.CoupleMin.first.x()))
                          .arg(QString::number(things[i]->Fere.CoupleMin.first.y())));
        thingsText.append(QString("Fere CoupleMin2: (%1,%2); ")
                          .arg(QString::number(things[i]->Fere.CoupleMin.second.x()))
                          .arg(QString::number(things[i]->Fere.CoupleMin.second.y())));
        thingsText.append(QString("Fere MaxDiametr: %1; ")
                          .arg(QString::number(things[i]->Fere.MaxDiametr)));
        data.MaxDiametr = things[i]->Fere.MaxDiametr;
        thingsText.append(QString("Fere AngleMax: %1; ")
                          .arg(QString::number(things[i]->Fere.AngleMax)));
        data.AngleMax = things[i]->Fere.AngleMax;
        thingsText.append(QString("Fere CoupleMax1: (%1,%2); ")
                          .arg(QString::number(things[i]->Fere.CoupleMax.first.x()))
                          .arg(QString::number(things[i]->Fere.CoupleMax.first.y())));
        thingsText.append(QString("Fere CoupleMax2: (%1,%2); ")
                          .arg(QString::number(things[i]->Fere.CoupleMax.second.x()))
                          .arg(QString::number(things[i]->Fere.CoupleMax.second.y())));
        thingsText.append(QString("Fere AverageDiametr: %1; ")
                          .arg(QString::number(things[i]->Fere.AverageDiametr)));
        data.AverageDiametr = things[i]->Fere.AverageDiametr;
        thingsText.append(QString("Fere MeanSquareDiametr: %1; ")
                          .arg(QString::number(things[i]->Fere.MeanSquareDiametr)));
        data.MeanSquareDiametr = things[i]->Fere.MeanSquareDiametr;
        thingsText.append(QString("Fere Valid: %1; ")
                          .arg(QString::number(things[i]->Fere.Valid)));
        data.FerValid = things[i]->Fere.Valid;
        thingsText.append("\n\n");
    }
    qDebug() << "thingsText"<< thingsText;
//    emit result(data);
    morphData = data;
}

