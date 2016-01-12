#include "sender.h"
#include "Core/anamnesmanager.h"
#include "Core/profilemanager.h"
#include "Core/databasemanager.h"
#include <QListWidgetItem>
#include <Markers/marker.h>
#include "recognizemediator.h"

Sender::Sender(QObject *parent) : QObject(parent)
{
    mediator = new RecognizeMediator(this);
 /*   connect(mediator, &RecognizeMediator::result, this,
            [&](MorphData d)
    {
        qDebug() << "lalsad"  << d.AverageRadius;
    }
    )*/;
}

void Sender::startOperation(const QString &path,
                            Core::DataBaseManager *dbm,
                            Core::AnamnesManager *am,
                            Core::ProfileManager *pm,
                            QVector<QPair<QListWidgetItem *, Marker *> > *markers)
{
    if(path.isEmpty())
    {
        qDebug() << "path" << path;
        return;
    }
    anamnesId = dbm->writeAnamnes(am);
    QImage image;
    image.load(path + "/Morph/morph.png");
    qDebug() <<  anamnesId <<  "profile id" <<
                 (profileId = dbm->
                 writeProfile(
                     pm,
                     anamnesId
                     ));
    dbM = dbm;

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
        MorphData data;
        qint64 markerID = dbm->writeMarker(marker,path, profileId);
        qDebug() << "lalsad"  << markerID <<
        (data = mediator->calculate(tmp,image)).AverageRadius;
        qDebug() << "marph" << dbm->writeMorphology(data, markerID);
    }
    qDebug() << "ВСЁ";
}
