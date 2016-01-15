#include "databasemanager.h"
#include "anamnesmanager.h"
#include "profilemanager.h"
#include "Markers/marker.h"
#include "morphdata.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimer>
#include <QHash>
#include <QDataStream>

using namespace Core;

DataBaseManager::DataBaseManager(QObject *parent, const char *driverName,
                                 int port, const QString& schemaName, uint checkTimeDiaposonMs) :
    QObject(parent),
    _db(QSqlDatabase::addDatabase(driverName)), _port(port), _schema_name(schemaName),
    _checkTimeDiaposonMs(checkTimeDiaposonMs)
{
    _previewHash = 0;
    _previewCheckTimer = new QTimer(this);
    QObject::connect(_previewCheckTimer,
            &QTimer::timeout,
            this,
            &DataBaseManager::checkPreview);
    _previewList = NULL;
}

DataBaseManager::~DataBaseManager()
{
    _db.close();
}

bool DataBaseManager::connect(const QString &user, const QString &host, const QString &pass, int mode)
{
    if(_db.isOpen())
        _db.close();
    _db.setUserName(user);
    _db.setHostName(host);
    _db.setPassword(pass);
    _db.setPort(_port);
    _db.setDatabaseName(_schema_name);
    _mode = (Mode)mode;
    bool retVal = _db.open();
    if(retVal)
    {
        qDebug() << "wow" << _mode;
//        QSqlQuery query;
//        query.exec("set character_set_database = 'utf8'");
//        qDebug() << "count is ok"<< query.exec("SELECT count(*) FROM anamnesis;");
//        qDebug() << query.lastError().text();
//        qDebug() << "next" << query.next();
//        qDebug() << "query.value(0)" << query.value(0).toInt();
        emit openMode(mode);
    }
    else qDebug() << _db.lastError().text();
    return retVal;
}

qint64 DataBaseManager::writeProfile(ProfileManager *profileManager, qint64 anamnesId)
{
    qDebug()  << "saddsa" << anamnesId;
    qint64 retVal = - 1;
    if(_db.isOpen() && 0 <= anamnesId )
    {
        _db.transaction();
        bool ok = true;
        QSqlQuery query;
        query.prepare("call Fill_patient_info(:sexIn, :diagName, "
                      ":SNILSIn, :INNin, :passportIn, :anamIn, :FIOin, "
                      ":insurnumIn, :OGRNIn, :InsurIn, :cardNoIn, "
                      ":BenefinNumIn, :birthDateIn, "
                      ":a1, :a2, :a3, :a4, :a5, :a6, :a7,"
                      ":b1, :b2, :b3, :b4, :b5, :b6, :b7);");
        query.bindValue(":sexIn", QVariant::fromValue(profileManager->sex()));
        query.bindValue(":diagName", QVariant::fromValue(profileManager->lineDiagnL()));
        query.bindValue(":SNILSIn", QVariant::fromValue(profileManager->lineSnilsID()));
        query.bindValue(":INNin", QVariant());
        query.bindValue(":passportIn", QVariant());
        query.bindValue(":anamIn", QVariant::fromValue(anamnesId));
        query.bindValue(":FIOin", QVariant::fromValue(profileManager->lineName()));
        query.bindValue(":insurnumIn", QVariant::fromValue(profileManager->lineMedValID()));
        query.bindValue(":OGRNIn",QVariant::fromValue(profileManager->linePSRN()));
        query.bindValue(":InsurIn", QVariant::fromValue(profileManager->lineMedComID()));
        query.bindValue(":cardNoIn", QVariant::fromValue(profileManager->lineMedCardID()));
        query.bindValue(":BenefinNumIn", QVariant::fromValue(profileManager->lineSale()));
        query.bindValue(":birthDateIn", QVariant::fromValue(profileManager->dateBth()));
        query.bindValue(":a1", QVariant::fromValue(profileManager->lineRegR()));
        query.bindValue(":a2", QVariant::fromValue(profileManager->lineDistrR()));
        query.bindValue(":a3", QVariant::fromValue(profileManager->lineLocR()));
        query.bindValue(":a4", QVariant::fromValue(profileManager->lineStrR()));
        query.bindValue(":a5", QVariant::fromValue(profileManager->lineHomR()));
        query.bindValue(":a6", QVariant::fromValue(profileManager->lineBuilR()));
        query.bindValue(":a7", QVariant::fromValue(profileManager->lineApR()));
        query.bindValue(":b1", QVariant::fromValue(profileManager->lineRegC()));
        query.bindValue(":b2", QVariant::fromValue(profileManager->lineDistrC()));
        query.bindValue(":b3", QVariant::fromValue(profileManager->lineLocC()));
        query.bindValue(":b4", QVariant::fromValue(profileManager->lineStrC()));
        query.bindValue(":b5", QVariant::fromValue(profileManager->lineHomC()));
        query.bindValue(":b6", QVariant::fromValue(profileManager->lineBuilC()));
        query.bindValue(":b7", QVariant::fromValue(profileManager->lineApC()));
        ok = query.exec();
        qDebug() << "ok?" << ok;
        qDebug() << query.lastError().text();
        query.next();
        query.exec("SELECT MAX(id) from patient_info;");
        query.next();
        retVal = query.value(0).toInt(&ok);
        qDebug() << query.lastError().text();
        _db.commit();
        qDebug() << "ok?" << ok;
    }
    return retVal;
}

qint64 DataBaseManager::writeAnamnes(AnamnesManager *anamnesManager)
{
    qDebug("call writeAnamnes");
    qint64 retVal = - 1;
    if(_db.isOpen())
    {
        _db.transaction();
        bool ok = true;
        QSqlQuery query;
        query.prepare("call Fill_Anamnesys_pg1(:dateIn,"
                      ":complIn,:SickIn,:LifeIn "
                      ",:deseasIn,:allergIn);");
        qDebug() <<"input datasince" << anamnesManager->dateSince();
        query.bindValue(":dateIn",QVariant::fromValue(anamnesManager->dateSince()));
        query.bindValue(":complIn",QVariant::fromValue(anamnesManager->textComplaint()));
        query.bindValue(":SickIn",QVariant::fromValue(anamnesManager->textAnDis()));
        query.bindValue(":LifeIn",QVariant::fromValue(anamnesManager->textAnLi()));
        query.bindValue(":deseasIn",QVariant::fromValue(anamnesManager->lineVen()));
        query.bindValue(":allergIn",QVariant::fromValue(anamnesManager->lineAler()));
        ok = query.exec();
        query.next();
        qDebug() << query.lastError().text();
        qDebug() << "saasd" << ok;
        query.prepare("CALL Fill_Anamnesys_pg2(:StateIn,"
                      ":PhysIn,:DietIn,"
                      ":skinIn,:edemIn,:lymphIn,"
                      ":tempIn,:respIn,:ChestIn,"
                      ":PercurIn,:BreathIn);");
        query.bindValue(":StateIn",QVariant::fromValue(anamnesManager->isCheckNorSt()));
        query.bindValue(":PhysIn",QVariant::fromValue(anamnesManager->linePhys()));
        query.bindValue(":DietIn",QVariant::fromValue(anamnesManager->lineFood()));
        query.bindValue(":skinIn",QVariant::fromValue(anamnesManager->lineSkin()));
        query.bindValue(":edemIn",QVariant::fromValue(anamnesManager->lineOedema()));
        query.bindValue(":lymphIn",QVariant::fromValue(anamnesManager->textLimpha()));
        query.bindValue(":tempIn",QVariant::fromValue(anamnesManager->lineTempr()));
        query.bindValue(":respIn",QVariant::fromValue(anamnesManager->lineRespR()));
        query.bindValue(":ChestIn",QVariant::fromValue(anamnesManager->lineThorax()));
        query.bindValue(":PercurIn",QVariant::fromValue(anamnesManager->linePercussion()));
        query.bindValue(":BreathIn",QVariant::fromValue(anamnesManager->textBreath()));
        ok &= query.exec();
        query.next();
        qDebug() << "saasd" << ok;
        //(in HeartBorIn text, in  HeartTonIn text, in  ArtPresIn text,
        //in  HeartRateIn text, in  PulseIn text, in  StomachIn text,
        //in  liverIn text, in  PasternIn text, in  stoolIn text, in  urineIn text)
        query.prepare("CALL Fill_Anamnesys_pg3(:HeartBorIn,"
                      ":HeartTonIn,:ArtPresIn,"
                      ":HeartRateIn,:PulseIn,:StomachIn,"
                      ":liverIn,:PasternIn,:stoolIn,"
                      ":urineIn);");
        query.bindValue(":HeartBorIn",QVariant::fromValue(anamnesManager->lineHeartBorders()));
        query.bindValue(":HeartTonIn",QVariant::fromValue(anamnesManager->lineSoniCordis()));
        query.bindValue(":ArtPresIn",QVariant::fromValue(anamnesManager->lineArtPre()));
        query.bindValue(":HeartRateIn",QVariant::fromValue(anamnesManager->linePulse()));
        query.bindValue(":PulseIn",QVariant::fromValue(anamnesManager->linePulse2()));
        query.bindValue(":StomachIn",QVariant::fromValue(anamnesManager->textStomach()));
        query.bindValue(":liverIn",QVariant::fromValue(anamnesManager->textLiver()));
        query.bindValue(":PasternIn",QVariant::fromValue(anamnesManager->textPasternatsky()));
        query.bindValue(":stoolIn",QVariant::fromValue(anamnesManager->lineFeces()));
        query.bindValue(":urineIn",QVariant::fromValue(anamnesManager->textUrination()));
        ok &= query.exec();
        query.next();
        query.prepare("CALL Fill_Anamnesys_pg4(:PreDiag,"
                      ":complIn,:anamnIn,:researchIn,"
                      ":treatmIn,:DisabilIn,:DoctIn)");
        query.bindValue(":PreDiag",QVariant::fromValue(anamnesManager->textDiagnosis()));
        query.bindValue(":complIn",QVariant::fromValue(anamnesManager->textByComplaint()));
        query.bindValue(":anamnIn",QVariant::fromValue(anamnesManager->textByAnamnes()));
        query.bindValue(":researchIn",QVariant::fromValue(anamnesManager->textPlanRes()));
        query.bindValue(":treatmIn",QVariant::fromValue(anamnesManager->textPlanTher()));
        query.bindValue(":DisabilIn",QVariant::fromValue(anamnesManager->lineIncapacitated()));
        query.bindValue(":DoctIn",QVariant::fromValue(anamnesManager->lineDoc()));
        ok &= query.exec();
        qDebug() << "ok?" << ok;
        qDebug() << query.lastError().text();
        query.next();
        query.exec("SELECT MAX(id) from anamnesis;");
        query.next();
        retVal = query.value(0).toInt(&ok);
        qDebug() << query.lastError().text();
        _db.commit();
        qDebug() << "ok?" << ok;
    }
    return retVal;
}

qint64 DataBaseManager::writeMarker(Marker *marker,
                                    const QString& imgPath,
                                    const QString& about,
                                    qint64 profileId)
{
    qDebug("call writeMarker");
    qint64 retVal = - 1;
    if(_db.isOpen())
    {
        _db.transaction();
        bool ok = true;
        QSqlQuery query;
        query.prepare("call Fill_FMarker(:mName,"
                      ":color, :thickness, :scale,"
                      ":inURL, :firstX, :firstY, :form);");
        query.bindValue(":mName", QVariant::fromValue(marker->text));
        query.bindValue(":thickness", QVariant());
        query.bindValue(":scale", QVariant());
        query.bindValue(":inURL", QVariant::fromValue(imgPath));
        query.bindValue(":form", marker->name);
        if(marker->name != "Polygon")
        {
            query.bindValue(":color", QVariant::fromValue(marker->item->color));
            qDebug() << "firstPoint" << marker->item->firstPoint;
            query.bindValue(":firstX", QVariant::fromValue(marker->item->firstPoint.x()));
            query.bindValue(":firstY", QVariant::fromValue(marker->item->firstPoint.y()));
            ok = query.exec();
            query.next();
//            _db.commit();
            qDebug() << query.lastError().text();
            qDebug() << "saasd" << ok; // zero means add to last added;
//            _db.transaction();
            query.prepare("CALL Fill_Point(:x, :y, :zero);");
            qDebug() << "secondPoint" << marker->item->secondPoint;
            query.bindValue(":x", QVariant::fromValue(marker->item->secondPoint.x()));
            query.bindValue(":y", QVariant::fromValue(marker->item->secondPoint.y()));
            query.bindValue(":zero", QVariant::fromValue(0));
            ok &= query.exec();
            query.next();
//            _db.commit();
            qDebug() << query.lastError().text();
            qDebug() << "saasd" << ok; // zero means add to last added;
        }
        else
        {
            query.bindValue(":color", QVariant::fromValue(marker->advancedItem->color));
            query.bindValue(":firstX", QVariant::fromValue(marker->advancedItem->points[0].x()));
            query.bindValue(":firstY", QVariant::fromValue(marker->advancedItem->points[0].y()));
            ok = query.exec();
            query.next();
//            _db.commit();
            qDebug() << query.lastError().text();
            qDebug() << "saasd" << ok; // zero means add to last added;
            for(int i = 1; i < marker->advancedItem->points.count(); ++i)
            {
//                _db.transaction();
                query.prepare("CALL Fill_Point(:x, :y, :zero);");
                qDebug() << marker->advancedItem->points[i];
                query.bindValue(":x", QVariant::fromValue(marker->advancedItem->points[i].x()));
                query.bindValue(":y", QVariant::fromValue(marker->advancedItem->points[i].y()));
                query.bindValue(":zero", QVariant::fromValue(0));
                ok &= query.exec();
                query.next();
//                _db.commit();
                qDebug() << query.lastError().text();
                qDebug() << "saasd" << ok; // zero means add to last added;
            }
        }
        query.prepare("call Connector_entry(:URL, :PatId, :about);");
        query.bindValue(":URL", QVariant::fromValue(imgPath));
        query.bindValue(":PatId", QVariant::fromValue(profileId));
        query.bindValue(":about", QVariant::fromValue(about));
        ok &= query.exec();
        query.next();
//                _db.commit();
        qDebug() << query.lastError().text();
        qDebug() << "CONNECTOR!!!111" << ok; // zero means add to last added;
//        _db.transaction();
        ok &= query.exec("SELECT MAX(id) from markFull;");
        query.next();
        retVal = query.value(0).toInt(&ok);
        qDebug() << query.lastError().text();
        _db.commit();
        qDebug() << "ok?" << ok;
    }
    return retVal;
}

qint64 DataBaseManager::writeMorphology(MorphData &data, qint64 markerId)
{
    qDebug("call writeMarker");
    qint64 retVal = - 1;
    if(_db.isOpen())
    {
        _db.transaction();
        bool ok = true;
        QSqlQuery query;
        query.prepare("call Fill_Morph(:Spots, "
                      ":SpotsSquare, :ExtCircuit8Len, :ExtCircuit4Len, :ExtPerimetr, "
                      ":IntCircuit8Len, :IntCircuit4Len, :IntPerimetr, :Square, "
                      ":Fullness, :ShapeFactor, :MarkF_id, :MinDiametr, :AngleMin, "
                      ":MaxDiametr, :AngleMax, :AverageDiametr, :MeanSquareDiametr, "
                      ":RadValid, :MaxRadius, :MinRadius, :AverageRadius, :MeanSquareRadius, "
                      ":InertiaMoment, :RelInertiaMoment, :FerValid);");
        query.bindValue(":Spots", QVariant::fromValue(data.Spots));
        query.bindValue(":SpotsSquare", QVariant::fromValue(data.SpotsSquare));
        query.bindValue(":ExtCircuit8Len", QVariant::fromValue(data.ExtCircuit8Len));
        query.bindValue(":ExtCircuit4Len", QVariant::fromValue(data.ExtCircuit4Len));
        query.bindValue(":ExtPerimetr", QVariant::fromValue(data.ExtPerimetr));
        query.bindValue(":IntCircuit8Len", QVariant::fromValue(data.IntCircuit8Len));
        query.bindValue(":IntCircuit4Len", QVariant::fromValue(data.IntCircuit4Len));
        query.bindValue(":IntPerimetr", QVariant::fromValue(data.IntPerimetr));
        query.bindValue(":Square", QVariant::fromValue(data.Square));
        query.bindValue(":Fullness", QVariant::fromValue(data.Fullness));
        query.bindValue(":ShapeFactor", QVariant::fromValue(data.ShapeFactor));
        query.bindValue(":MarkF_id", QVariant::fromValue(markerId));
        query.bindValue(":MinDiametr", QVariant::fromValue(data.MinDiametr));
        query.bindValue(":AngleMin", QVariant::fromValue(data.AngleMin));
        query.bindValue(":MaxDiametr", QVariant::fromValue(data.MaxDiametr));
        query.bindValue(":AngleMax", QVariant::fromValue(data.AngleMax));
        query.bindValue(":AverageDiametr", QVariant::fromValue(data.AverageDiametr));
        query.bindValue(":MeanSquareDiametr", QVariant::fromValue(data.MeanSquareDiametr));
        query.bindValue(":RadValid", QVariant::fromValue(data.RadValid));
        query.bindValue(":MaxRadius", QVariant::fromValue(data.MaxRadius));
        query.bindValue(":MinRadius", QVariant::fromValue(data.MinRadius));
        query.bindValue(":AverageRadius", QVariant::fromValue(data.AverageRadius));
        query.bindValue(":MeanSquareRadius", QVariant::fromValue(data.MeanSquareRadius));
        query.bindValue(":InertiaMoment", QVariant::fromValue(data.InertiaMoment));
        query.bindValue(":RelInertiaMoment", QVariant::fromValue(data.RelInertiaMoment));
        query.bindValue(":FerValid", QVariant::fromValue(data.FerValid));
        ok = query.exec();
        query.next();
        qDebug() << query.lastError().text();
        qDebug() << "saasd" << ok; // zero means add to last added;
        query.exec("SELECT MAX(id) from morph_tthing;");
        query.next();
        retVal = query.value(0).toInt(&ok);
        qDebug() << query.lastError().text();
        _db.commit();
        qDebug() << "ok?" << ok;
    }
    return retVal;
}

QString DataBaseManager::readDiagnosisById(qint64 id, bool* ok)
{
    bool myOk = false;
    QString retVal;
    if(_db.isOpen())
    {
        _db.transaction();
        QSqlQuery query;
        myOk = query.exec(QString("SELECT name FROM diagnoses WHERE id = %1;")
                            .arg(id));
        if(query.next())
        {
            retVal = query.value(0).toString();
        }
        qDebug() << query.lastError().text();
        qDebug() << "readDiagnosisById is ok" << myOk;
        _db.commit();
    }
    if(ok != NULL)
        *ok = myOk;
    return retVal;
}

void DataBaseManager::readPreview(QList<QPair<qint64, QString> > *previewList)
{
    _previewList =  previewList;
    checkPreview();
}
void DataBaseManager::checkPreview()
{
//    _previewCheckTimer->start(_checkTimeDiaposonMs);
    QList<QPair<qint64, QString> > retVal;
    uint curHash = 0;
    QByteArray ba;
    QDataStream ds(&ba,QIODevice::WriteOnly);
    if(_db.isOpen())
    {
        qint64 id;
        QString str;
        _db.transaction();
        QSqlQuery query;
        query.exec("CALL View_Patient_short();");
        while(query.next())
        {
            id = query.value(0).toLongLong();
            str = query.value(1).toString() + " " + query.value(2).toString();
            retVal << QPair<qint64, QString>(id,str);
        }

        qDebug() << retVal.count() << "query.size()" << query.size();
        ds << retVal;
        curHash = qHash(ba);
        _db.commit();
    }
    if (curHash != _previewHash)
    {
        _previewHash = curHash;
        *_previewList = retVal;
        qDebug() << "list" << _previewList->count();
        emit updatePreviewListWidget();
    }
}

bool DataBaseManager::readProfileAndAnamnes(ProfileManager* profileManager,AnamnesManager* anamnesManager, qint64 profileId)
{
    bool retVal = false;
    if(_db.isOpen())
    {
        _db.transaction();
        QSqlQuery query;
        retVal = query.exec(QString("CALL View_Patient_info_byid(%1);").arg(profileId));
//        query.bindValue(":profileId",profileId);
//        retVal = query.exec();
        qDebug() << query.lastError().text() << query.size();
        if(query.next())
        {
            qDebug("whoa");
            profileManager->setSex(query.value(1).toBool());
            profileManager->setLineDiagnL(query.value(2).toString());
            profileManager->setLineSnilsID(query.value(3).toString());
            profileManager->setLineName(query.value(7).toString());
            profileManager->setLineMedValID(query.value(8).toString());
            profileManager->setLinePSRN(query.value(9).toString());
            profileManager->setLineMedComID(query.value(10).toString());
            profileManager->setLineMedCardID(query.value(11).toString());
            profileManager->setLineSale(query.value(12).toString());
            profileManager->setLineRegR(query.value(13).toString());
            profileManager->setLineDistrR(query.value(14).toString());
            profileManager->setLineLocR(query.value(15).toString());
            profileManager->setLineStrR(query.value(16).toString());
            profileManager->setLineHomR(query.value(17).toString());
            profileManager->setLineBuilR(query.value(18).toString());
            profileManager->setLineApR(query.value(19).toString());
            profileManager->setLineRegC(query.value(20).toString());
            profileManager->setLineDistrC(query.value(21).toString());
            profileManager->setLineLocC(query.value(22).toString());
            profileManager->setLineStrC(query.value(23).toString());
            profileManager->setLineHomC(query.value(24).toString());
            profileManager->setLineBuilC(query.value(25).toString());
            profileManager->setLineApC(query.value(26).toString());
            profileManager->setDateBth(query.value(27).toDate());
        }
        _db.commit();
        retVal &= readAnamnes(anamnesManager,profileId);
    }
    return retVal;
}

bool DataBaseManager::readAnamnes(AnamnesManager *anamnesManager, qint64 profileId)
{
    bool retVal = false;
    if(_db.isOpen())
    {
        _db.transaction();
        qDebug() << "again";
        QSqlQuery query;
        retVal &= query.exec(QString("CALL View_Anamnesis_byId(%1);").arg(profileId));

        if(query.next())
        {
            anamnesManager->setDateSince(query.value(1).toDate());
            anamnesManager->setTextComplaint(query.value(2).toString());
            anamnesManager->setTextAnDis(query.value(3).toString());
            anamnesManager->setTextAnLi(query.value(4).toString());
            anamnesManager->setLineVen(query.value(5).toString());
            anamnesManager->setLineAler(query.value(6).toString());
            anamnesManager->setCheckNorSt(query.value(7).toBool());
            anamnesManager->setLinePhys(query.value(8).toString());
            anamnesManager->setLineFood(query.value(9).toString());
            anamnesManager->setLineSkin(query.value(10).toString());
            anamnesManager->setLineOedema(query.value(11).toString());
            anamnesManager->setTextLimpha(query.value(12).toString());
            anamnesManager->setLineTempr(query.value(13).toString());
            anamnesManager->setLineRespR(query.value(14).toString());
            anamnesManager->setLineThorax(query.value(15).toString());
            anamnesManager->setLinePercussion(query.value(16).toString());
            anamnesManager->setTextBreath(query.value(17).toString());
            anamnesManager->setLineHeartBorders(query.value(18).toString());
            anamnesManager->setLineSoniCordis(query.value(19).toString());
            anamnesManager->setLineArtPre(query.value(20).toString());
            anamnesManager->setLinePulse(query.value(21).toString());
            anamnesManager->setLinePulse2(query.value(22).toString());
            anamnesManager->setTextStomach(query.value(23).toString());
            anamnesManager->setTextLiver(query.value(24).toString());
            anamnesManager->setTextPasternatsky(query.value(25).toString());
            anamnesManager->setLineFeces(query.value(26).toString());
            anamnesManager->setTextUrination(query.value(27).toString());
            anamnesManager->setTextDiagnosis(query.value(28).toString());
            anamnesManager->setTextByComplaint(query.value(29).toString());
            anamnesManager->setTextByAnamnes(query.value(30).toString());
            anamnesManager->setTextPlanRes(query.value(31).toString());
            anamnesManager->setTextPlanTher(query.value(32).toString());
            anamnesManager->setLineIncapacitated(query.value(33).toString());
            anamnesManager->setLineDoc(query.value(34).toString());
        }
        _db.commit();
    }
    return retVal;
}

bool DataBaseManager::readMorphology(QMap<qint64, QVector<MorphData *>* > *morphMap)
{
    for(auto it = morphMap->begin(); it != morphMap->end(); ++it)
    {
        qDeleteAll(*it.value());
    }
    qDeleteAll(*morphMap);
    morphMap->clear();
    QSet<qint64> ids;
    bool retVal = false;
    if(_db.isOpen())
    {
        _db.transaction();
        qDebug() << "again";
        QSqlQuery query;
        retVal = query.exec(QString("SELECT diagnoses_id FROM patient_info;"));
        while(query.next())
        {
            ids.insert(query.value(0).toLongLong());
        }
        for(auto it = ids.begin(); it != ids.end(); ++it)
        {
            QVector<MorphData *>* tmpVData = new QVector<MorphData *>;
            retVal &= query.exec(QString("CALL View_Morph_ByDiag(%1);")
                                 .arg(*it));
            while(query.next())
            {
                qDebug() << "ok View_Morph_ByDiag";
                MorphData* data = new MorphData;
                int i = 0;
                data->MarkId = query.value(i).toLongLong();
                i++;
                data->Spots = query.value(i).toLongLong();
                i++;
                data->SpotsSquare = query.value(i).toLongLong();
                i++;
                data->ExtCircuit8Len = query.value(i).toLongLong();
                i++;
                data->ExtCircuit4Len = query.value(i).toLongLong();
                i++;
                data->ExtPerimetr = query.value(i).toLongLong();
                i++;
                data->IntCircuit8Len = query.value(i).toLongLong();
                i++;
                data->IntCircuit4Len = query.value(i).toLongLong();
                i++;
                data->IntPerimetr = query.value(i).toLongLong();
                i++;
                data->Square = query.value(i).toLongLong();
                i++;
                data->Fullness = query.value(i).toReal();
                i++;
                data->ShapeFactor = query.value(i).toReal();
                //Fere
                i++;
                data->MinDiametr = query.value(i).toReal();
                i++;
                data->AngleMin = query.value(i).toLongLong();
                i++;
                data->MaxDiametr = query.value(i).toReal();
                i++;
                data->AngleMax = query.value(i).toLongLong();
                i++;
                data->AverageDiametr = query.value(i).toReal();
                i++;
                data->MeanSquareDiametr = query.value(i).toReal();
                i++;
                data->FerValid = query.value(i).toBool();
                // Radius
                i++;
                data->MaxRadius = query.value(i).toReal();
                i++;
                data->MinRadius = query.value(i).toReal();
                i++;
                data->AverageRadius = query.value(i).toReal();
                i++;
                data->MeanSquareRadius = query.value(i).toReal();
                i++;
                data->InertiaMoment = query.value(i).toReal();
                i++;
                data->RelInertiaMoment = query.value(i).toReal();
                i++;
                data->RadValid = query.value(i).toBool();
                tmpVData->push_back(data);
            }
            morphMap->insert(*it, tmpVData);
        }
        _db.commit();
    }
    return retVal;
}


