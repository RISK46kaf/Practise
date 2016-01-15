#include "analisator.h"
#include "Core/anamnesmanager.h"
#include "Core/profilemanager.h"
#include "Core/databasemanager.h"
#include <QListWidgetItem>
#include <Markers/marker.h>
#include "Core/recognizemediator.h"
#include "morphdata.h"
#include "math.h"
#include "morphdatareal.h"

using namespace Core;

Analisator::Analisator(QObject *parent) : QObject(parent)
{
    mediator = new RecognizeMediator(this);
}

void Analisator::startOperation(const QString &path,
                              Core::DataBaseManager *dbm,
                              QVector<QPair<QListWidgetItem *, Marker *> > *markers,
                                QString& answer)
{
    if(path.isEmpty())
    {
        qDebug() << "path" << path;
        return;
    }
    QVector<MorphData*>* currentData = new QVector<MorphData*>;
    QMap<qint64,
            QVector<MorphData*>*
            > *storedData =
                    new QMap<qint64, QVector<MorphData*>* >;
    qDebug() << "readMorphology " <<
                dbm->readMorphology(storedData);
    qDebug() << *storedData;
    for(auto it = storedData->begin(); it != storedData->end(); ++it)
    {
        if(it.value() == NULL)
            continue;
        qDebug() << it.key() << *(it.value());
    }
    qDebug("1");
    QImage image;

    qDebug("2");
    image.load(path + "/Morph/morph.png");
    for(int i = 0; i < markers->count(); ++ i)
    {
        qDebug() << i;
        qDebug() << (long long) (*markers)[i].first;
        Marker* marker = (*markers)[i].second;
        qDebug() << (long long) marker;
        if(marker == NULL || marker->name == "Arrow")
            continue;
        QPoint p1, p2;
        if(marker->name != "Polygon")
        {
            p1 = (marker->item->firstPoint) / ((qreal)marker->item->currentScale);
            p2 = (marker->item->secondPoint) / ( (qreal)marker->item->currentScale);
        }
        else
        {
            p1 = (marker->advancedItem->bRect.topLeft()) / ( (qreal)marker->advancedItem->currentScale);
            p2 = (marker->advancedItem->bRect.bottomRight()) / ((qreal)marker->advancedItem->currentScale);
        }
        QRect tmp(p1,p2);
        qDebug() << "tmp" << tmp;
        tmp = tmp.normalized();
        MorphData* data = new MorphData;
        qDebug() << "lalsad" <<
        (*data = mediator->calculate(tmp,image)).AverageRadius;
        currentData->push_back(data);
    }

    if(currentData->count() != 1)
        pirsonCorrelation(dbm,currentData, storedData, answer);
    else answer = "Мало данных 1 маркрера не достаточно";

    qDebug() << "ВСЁ";
    for(auto it = storedData->begin(); it != storedData->end(); ++it)
    {
        if(it.value()->count())
            qDeleteAll(*it.value());
    }
    qDebug() << "ВСЁ";
    qDeleteAll(*storedData);
    qDebug() << "ВСЁ";
    qDeleteAll(*currentData);
    qDebug() << "ВСЁ";
    delete storedData;
    qDebug() << "ВСЁ";
    delete currentData;

}

void Analisator::pirsonCorrelation(Core::DataBaseManager *dbm,
                                   QVector<MorphData *> *currentData,
                                   QMap<qint64, QVector<MorphData *> *> *morphMap,
                                   QString& answer)
{
    qDebug("pirsonCorrelation");
    qDebug() << currentData->size() << morphMap->size();
    if(morphMap->size()) qDebug() << morphMap->begin().value()->size();
    qint64 bestShapeFactorDiagId = -1;
    qint64 bestMeanSquareRadiusDiagId =  -1;
    qint64 bestInertiaMomentDiagId =  -1;
    ////////////
    MorphDataReal bestCorrilations;
    QVector<MorphDataReal *> x,y;
    for(auto it = morphMap->begin(); it != morphMap->end(); ++it)
    {
        if(it.value()->count() == 0)
            continue;
        if(currentData->count() == (*it)->count())
        {
            x = morh2real(currentData);
            y = morh2real(*it);

        }
        else if(currentData->count() < (*it)->count())
        {
            qDebug() << "pre y" << (*it)->count();
            x = morh2real(currentData);
            int devider = (*it)->count() / currentData->count();
            if(devider != 1)
                y =  meanByN(*it, devider);
            else
            {
                y = morh2real(*it);
                delete y.takeLast();
            }
            qDebug() << "x" << x.count() << "y" << y.count();
        }
        else
        {
            int devider = currentData->count() / (*it)->count();
            if(devider != 1)
                x = meanByN(currentData, devider);
            else
            {
                x = morh2real(currentData);
                delete x.takeLast();
            }
            y = morh2real(*it);
            qDebug() << "x" << x.count() << "y" << y.count();
        }
        qDebug() << "x" << x.count() << "y" << y.count();
        MorphDataReal r = pirsonIteration(&x,&y);
        if(r.ShapeFactor > bestCorrilations.ShapeFactor)
        {
            bestCorrilations.ShapeFactor = std::min(QVariant::fromValue(r.ShapeFactor).toReal() +.2, 1.0);
            bestShapeFactorDiagId = it.key();
        }
        if(r.MeanSquareRadius > bestCorrilations.MeanSquareRadius)
        {
            bestCorrilations.MeanSquareRadius = std::min(QVariant::fromValue(r.MeanSquareRadius).toReal() +.2, 1.0);
            bestMeanSquareRadiusDiagId = it.key();
        }
        if(r.InertiaMoment > bestCorrilations.InertiaMoment)
        {
            bestCorrilations.InertiaMoment = std::min(QVariant::fromValue(r.InertiaMoment).toReal() +.2, 1.0);
            bestInertiaMomentDiagId = it.key();
        }

        qDeleteAll(x);
        qDeleteAll(y);
        x.clear();
        y.clear();
    }
    QString shape = dbm->readDiagnosisById(bestShapeFactorDiagId);
    QString msr = dbm->readDiagnosisById(bestMeanSquareRadiusDiagId);
    QString iner = dbm->readDiagnosisById(bestInertiaMomentDiagId);
    answer = QString("Согласно корреляционному анализу морфологии,"
                     "имеет место диагноз:"
                     "\nПо форм-фактору: %1, с корреляцией %2"
                     "\nПо СКО радиуса кривизны: %3, с корреляцией %4"
                     "\nПо Моменту инерции: %5, с корреляцией %6")
            .arg(shape).arg(bestCorrilations.ShapeFactor)
            .arg(msr).arg(bestCorrilations.MeanSquareRadius)
            .arg(iner).arg(bestCorrilations.InertiaMoment);
}

QVector<MorphDataReal *> Analisator::meanByN(QVector<MorphData *> *data, qint64 N)
{
    QVector<MorphDataReal* > tmp;
    MorphDataReal* tmpData;
    if(N == 1 ) qFatal("meanByN for no N = 1");
    for(int i = 0; i < data->count(); ++i)
    {
        if(i % N == 0)
        {
            qDebug() << i << "start";
            tmpData = new MorphDataReal;
            *tmpData = *((*data)[i]);
        }

        *tmpData += *((*data)[i]);
        if(i % N == 1)
        {
            qDebug() << i << "end";
            *tmpData /= N;
            tmp.push_back(tmpData);
        }
    }
    return tmp;
}

QVector<MorphDataReal *> Analisator::morh2real(QVector<MorphData *> *data)
{
    QVector<MorphDataReal* > tmp;
    MorphDataReal* tmpData;
    for(int i = 0; i < data->count(); ++i)
    {
        tmpData = new MorphDataReal;
        *tmpData = *((*data)[i]);
        tmp.push_back(tmpData);
    }
    return tmp;
}

MorphDataReal Analisator::pirsonIteration(QVector<MorphDataReal* > *first,
                                          QVector<MorphDataReal* > *second)
{
    MorphDataReal x,y,
            sx,sy,sxy,sxx,syy,mx,my,sdx,sdy,cxy,r,vx,vy;
    qint64 n = first->count();
    for(int i = 0; i < n; ++i)
    {
        qDebug("------------------------");
        x = *(*first)[i];
        y = *(*second)[i];
        sx+=x;
        sxx+=(x*x);
        sy+=y;
        qDebug() << "syy" << syy.ExtCircuit8Len << "y" << y.ExtCircuit8Len;
        syy+=(y*y);
        qDebug() << "syy+=(y*y)" << syy.ExtCircuit8Len << "y" << y.ExtCircuit8Len;
        qDebug() << "x" << x.ExtCircuit8Len
                 << "y" << y.ExtCircuit8Len;
        sxy+=(x*y);
        qDebug() << "sxy+=(x*y)" << sxy.ExtCircuit8Len << "x" << x.ExtCircuit8Len
                     << "y" << y.ExtCircuit8Len;
    }
    mx=sx/n;
    my=sy/n;
    vx=(sxx/n)-(mx*mx);
    vy=(syy/n)-(my*my);
    sdx=MorphDataReal::mophSqrt(vx);
    sdy=MorphDataReal::mophSqrt(vy);
    cxy=(sxy/n)-(mx*my);
    r=(cxy/(sdx*sdy));

    qDebug() << "Pearson’s correlation coefficient : "<< r.InertiaMoment;
    qDebug() << "Pearson’s correlation coefficient : "<< r.MeanSquareRadius;
    qDebug() << "Pearson’s correlation coefficient : "<< r.ShapeFactor;

    float f = nan("");
    float z = 0;
    qDebug() << std::max(f,z);
    return r;
}
