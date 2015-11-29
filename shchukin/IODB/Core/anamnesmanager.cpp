#include "anamnesmanager.h"
#include <QMetaProperty>
#include <QDebug>

using namespace Core;

AnamnesManager::AnamnesManager(QObject *parent) : QObject(parent)
{
    setObjectName("AnamnesManager");
    resetAll();
}

AnamnesManager::AnamnesManager(const AnamnesManager &other)
{
    _dateSince = other._dateSince;
    _textComplaint = other._textComplaint;
    _textAnDis = other._textAnDis;
    _textAnLi = other._textAnLi;
    _lineVen = other._lineVen;
    _lineAler = other._lineAler;
    _checkNorSt = other._checkNorSt;
    _linePhys = other._linePhys;
    _lineFood = other._linePhys;
    _lineSkin = other._lineSkin;
    _lineOedema = other._lineOedema;
    _textLimpha = other._textLimpha;
    _lineTempr = other._lineTempr;
    _lineRespR = other._lineRespR;
    _lineThorax = other._lineThorax;
    _linePercussion = other._linePercussion;
    _textBreath = other._textBreath;
    _lineHeartBorders = other._lineHeartBorders;
    _lineSoniCordis = other._lineSoniCordis;
    _lineArtPre = other._lineArtPre;
    _linePulse = other._linePulse;
    _linePulse2 = other._linePulse2;
    _lineTongue = other._lineTongue;
    _textStomach = other._textStomach;
    _textLiver = other._textLiver;
    _textPasternatsky = other._textPasternatsky;
    _lineFeces = other._lineFeces;
    _textUrination = other._textUrination;
    _textDiagnosis = other._textDiagnosis;
    _textByComplaint = other._textByComplaint;
    _textByAnamnes = other._textByAnamnes;
    _textPlanRes = other._textPlanRes;
    _textPlanTher = other._textPlanTher;
    _lineIncapacitated = other._lineIncapacitated;
    _lineDoc = other._lineDoc;
}

AnamnesManager &AnamnesManager::operator=(const AnamnesManager &other)
{
    _dateSince = other._dateSince;
    _textComplaint = other._textComplaint;
    _textAnDis = other._textAnDis;
    _textAnLi = other._textAnLi;
    _lineVen = other._lineVen;
    _lineAler = other._lineAler;
    _checkNorSt = other._checkNorSt;
    _linePhys = other._linePhys;
    _lineFood = other._linePhys;
    _lineSkin = other._lineSkin;
    _lineOedema = other._lineOedema;
    _textLimpha = other._textLimpha;
    _lineTempr = other._lineTempr;
    _lineRespR = other._lineRespR;
    _lineThorax = other._lineThorax;
    _linePercussion = other._linePercussion;
    _textBreath = other._textBreath;
    _lineHeartBorders = other._lineHeartBorders;
    _lineSoniCordis = other._lineSoniCordis;
    _lineArtPre = other._lineArtPre;
    _linePulse = other._linePulse;
    _linePulse2 = other._linePulse2;
    _lineTongue = other._lineTongue;
    _textStomach = other._textStomach;
    _textLiver = other._textLiver;
    _textPasternatsky = other._textPasternatsky;
    _lineFeces = other._lineFeces;
    _textUrination = other._textUrination;
    _textDiagnosis = other._textDiagnosis;
    _textByComplaint = other._textByComplaint;
    _textByAnamnes = other._textByAnamnes;
    _textPlanRes = other._textPlanRes;
    _textPlanTher = other._textPlanTher;
    _lineIncapacitated = other._lineIncapacitated;
    _lineDoc = other._lineDoc;
    return *this;
}

void AnamnesManager::resetAll()
{
    const QMetaObject* meta = metaObject();
    for(int i = 0; i < meta->propertyCount(); ++i)
    {
        if(meta->property(i).isResettable())
            meta->property(i).reset(this);
    }
}

QDate AnamnesManager::dateSince() const
{
    return _dateSince;
}

void AnamnesManager::unsetDateSince()
{
    _dateSince = QDate::fromString("01.01.2000","dd.MM.yyyy");
    emit dateSinceChanged(_dateSince);
}

void AnamnesManager::setDateSince(const QDate &dateSince)
{
    _dateSince = dateSince;
    qDebug() << "laladsd" << dateSince;
    emit dateSinceChanged(_dateSince);
}

QString AnamnesManager::textComplaint() const
{
    return _textComplaint;
}

void AnamnesManager::unsetTextComplaint()
{
    _textComplaint.clear();
    emit textComplaintChanged(_textComplaint);
}

void AnamnesManager::setTextComplaint(const QString &textComplaint)
{
    _textComplaint = textComplaint;
    emit textComplaintChanged(_textComplaint);
}

QString AnamnesManager::textAnDis() const
{
    return _textAnDis;
}

void AnamnesManager::unsetTextAnDis()
{
    _textAnDis.clear();
    emit textAnDisChanged(_textAnDis);
}

void AnamnesManager::setTextAnDis(const QString &textAnDis)
{
    _textAnDis = textAnDis;
    emit textAnDisChanged(_textAnDis);
}

QString AnamnesManager::textAnLi() const
{
    return _textAnLi;
}

void AnamnesManager::unsetTextAnLi()
{
    _textAnLi.clear();
    emit textAnLiChanged(_textAnLi);
}

void AnamnesManager::setTextAnLi(const QString &textAnLi)
{
    _textAnLi = textAnLi;
    emit textAnLiChanged(_textAnLi);
}

QString AnamnesManager::lineVen() const
{
    return _lineVen;
}

void AnamnesManager::unsetLineVen()
{
    _lineVen.clear();
    emit lineVenChanged(_lineVen);
}

void AnamnesManager::setLineVen(const QString &lineVen)
{
    _lineVen = lineVen;
    emit lineVenChanged(_lineVen);
}

QString AnamnesManager::lineAler() const
{
    return _lineAler;
}

void AnamnesManager::unsetLineAler()
{
    _lineAler.clear();
    emit lineAlerChanged(_lineAler);
}

void AnamnesManager::setLineAler(const QString &lineAler)
{
    _lineAler = lineAler;
    emit lineAlerChanged(_lineAler);
}

bool AnamnesManager::isCheckNorSt() const
{
    return _checkNorSt;
}

void AnamnesManager::unsetCheckNorSt()
{
    _checkNorSt = true;
    emit checkNorStChanged(_checkNorSt);
}

void AnamnesManager::setCheckNorSt(bool checkNorSt)
{
    _checkNorSt = checkNorSt;
    emit checkNorStChanged(_checkNorSt);
}

QString AnamnesManager::linePhys() const
{
    return _linePhys;
}

void AnamnesManager::unsetLinePhys()
{
    _linePhys.clear();
    emit linePhysChanged(_linePhys);
}

void AnamnesManager::setLinePhys(const QString &linePhys)
{
    _linePhys = linePhys;
    emit linePhysChanged(_linePhys);
}

QString AnamnesManager::lineFood() const
{
    return _lineFood;
}

void AnamnesManager::unsetLineFood()
{
    _lineFood.clear();
    emit lineFoodChanged(_lineFood);
}

void AnamnesManager::setLineFood(const QString &lineFood)
{
    _lineFood = lineFood;
    emit lineFoodChanged(_lineFood);
}

QString AnamnesManager::lineSkin() const
{
    return _lineSkin;
}

void AnamnesManager::unsetLineSkin()
{
    _lineSkin.clear();
}

void AnamnesManager::setLineSkin(const QString &lineSkin)
{
    _lineSkin = lineSkin;
    emit lineSkinChanged(_lineSkin);
}

QString AnamnesManager::lineOedema() const
{
    return _lineOedema;
}

void AnamnesManager::setLineOedema(const QString &lineOedema)
{
    _lineOedema = lineOedema;
    emit lineOedemaChanged(_lineOedema);
}

void AnamnesManager::unsetLineOedema()
{
    _lineOedema.clear();
    emit lineOedemaChanged(_lineOedema);
}

QString AnamnesManager::textLimpha() const
{
    return _textLimpha;
}

void AnamnesManager::setTextLimpha(const QString &textLimpha)
{
    _textLimpha = textLimpha;
    emit textLimphaChanged(_textLimpha);
}

void AnamnesManager::unsetTextLimpha()
{
    _textLimpha.clear();
    emit textLimphaChanged(_textLimpha);
}

QString AnamnesManager::lineTempr() const
{
    return _lineTempr;
}

void AnamnesManager::setLineTempr(const QString &lineTempr)
{
    _lineTempr = lineTempr;
    emit lineTemprChanged(_lineTempr);
}

void AnamnesManager::unsetLineTempr()
{
    _lineTempr.clear();
    emit lineTemprChanged(_lineTempr);
}

QString AnamnesManager::lineRespR() const
{
    return _lineRespR;
}

void AnamnesManager::setLineRespR(const QString &lineRespR)
{
    _lineRespR = lineRespR;
    emit lineRespRChanged(_lineRespR);
}

void AnamnesManager::unsetLineRespR()
{
    _lineRespR.clear();
    emit lineRespRChanged(_lineRespR);
}

QString AnamnesManager::lineThorax() const
{
    return _lineThorax;
}

void AnamnesManager::setLineThorax(const QString &lineThorax)
{
    _lineThorax = lineThorax;
    emit lineThoraxChanged(_lineThorax);
}

void AnamnesManager::unsetLineThorax()
{
    _lineThorax.clear();
    emit lineThoraxChanged(_lineThorax);
}

QString AnamnesManager::linePercussion() const
{
    return _linePercussion;
}

void AnamnesManager::setLinePercussion(const QString &linePercussion)
{
    _linePercussion = linePercussion;
    emit linePercussionChanged(_linePercussion);
}

void AnamnesManager::unsetLinePercussion()
{
    _linePercussion.clear();
    emit linePercussionChanged(_linePercussion);
}

QString AnamnesManager::textBreath() const
{
    return _textBreath;
}

void AnamnesManager::setTextBreath(const QString &textBreath)
{
    _textBreath = textBreath;
    emit textBreathChanged(_textBreath);
}

void AnamnesManager::unsetTextBreath()
{
    _textBreath.clear();
    emit textBreathChanged(_textBreath);
}

QString AnamnesManager::lineHeartBorders() const
{
    return _lineHeartBorders;
}

void AnamnesManager::setLineHeartBorders(const QString &lineHeartBorders)
{
    _lineHeartBorders = lineHeartBorders;
    emit lineHeartBordersChanged(_lineHeartBorders);
}

void AnamnesManager::unsetLineHeartBorders()
{
    _lineHeartBorders.clear();
    emit lineHeartBordersChanged(_lineHeartBorders);
}

QString AnamnesManager::lineSoniCordis() const
{
    return _lineSoniCordis;
}

void AnamnesManager::setLineSoniCordis(const QString &lineSoniCordis)
{
    _lineSoniCordis = lineSoniCordis;
    emit lineSoniCordisChanged(_lineSoniCordis);
}

void AnamnesManager::unsetLineSoniCordis()
{
    _lineSoniCordis.clear();
    emit lineSoniCordisChanged(_lineSoniCordis);
}

QString AnamnesManager::lineArtPre() const
{
    return _lineArtPre;
}

void AnamnesManager::setLineArtPre(const QString &lineArtPre)
{
    _lineArtPre = lineArtPre;
    emit lineArtPreChanged(_lineArtPre);
}

void AnamnesManager::unsetLineArtPre()
{
    _lineArtPre.clear();
    emit lineArtPreChanged(_lineArtPre);
}

QString AnamnesManager::linePulse() const
{
    return _linePulse;
}

void AnamnesManager::setLinePulse(const QString linePulse)
{
    _linePulse = linePulse;
    emit linePulseChanged(_linePulse);
}

void AnamnesManager::unsetLinePulse()
{
    _linePulse.clear();
    emit linePulseChanged(_linePulse);
}

QString AnamnesManager::linePulse2() const
{
    return _linePulse2;
}

void AnamnesManager::setLinePulse2(const QString linePulse2)
{
    _linePulse2 = linePulse2;
    emit linePulse2Changed(_linePulse2);
}

void AnamnesManager::unsetLinePulse2()
{
    _linePulse2.clear();
    emit linePulse2Changed(_linePulse2);
}

QString AnamnesManager::lineTongue() const
{
    return _lineTongue;
}

void AnamnesManager::setLineTongue(const QString &lineTongue)
{
    _lineTongue = lineTongue;
    emit lineTongueChanged(_lineTongue);
}

void AnamnesManager::unsetLineTongue()
{
    _lineTongue.clear();
    emit lineTongueChanged(_lineTongue);
}

QString AnamnesManager::textStomach() const
{
    return _textStomach;
}

void AnamnesManager::setTextStomach(const QString &textStomach)
{
    _textStomach = textStomach;
    emit textStomachChanged(_textStomach);
}

void AnamnesManager::unsetTextStomach()
{
    _textStomach.clear();
    emit textStomachChanged(_textStomach);
}

QString AnamnesManager::textLiver() const
{
    return _textLiver;
}

void AnamnesManager::setTextLiver(const QString &textLiver)
{
    _textLiver = textLiver;
    emit textLiverChanged(_textLiver);
}

void AnamnesManager::unsetTextLiver()
{
    _textLiver.clear();
    emit textLiverChanged(_textLiver);
}

QString AnamnesManager::textPasternatsky() const
{
    return _textPasternatsky;
}

void AnamnesManager::setTextPasternatsky(const QString &textPasternatsky)
{
    _textPasternatsky = textPasternatsky;
    emit textPasternatskyChanged(_textPasternatsky);
}

void AnamnesManager::unsetTextPasternatsky()
{
    _textPasternatsky.clear();
    emit textPasternatskyChanged(_textPasternatsky);
}

QString AnamnesManager::lineFeces() const
{
    return _lineFeces;
}

void AnamnesManager::setLineFeces(const QString &lineFeces)
{
    _lineFeces = lineFeces;
    emit lineFecesChanged(_lineFeces);
}

void AnamnesManager::unsetLineFeces()
{
    _lineFeces.clear();
    emit lineFecesChanged(_lineFeces);
}

QString AnamnesManager::textUrination() const
{
    return _textUrination;
}

void AnamnesManager::setTextUrination(const QString &textUrination)
{
    _textUrination = textUrination;
    emit textUrinationChanged(_textUrination);
}

void AnamnesManager::unsetTextUrination()
{
    _textUrination.clear();
    emit textUrinationChanged(_textUrination);
}

QString AnamnesManager::textDiagnosis() const
{
    return _textDiagnosis;
}

void AnamnesManager::setTextDiagnosis(const QString &textDiagnosis)
{
    _textDiagnosis = textDiagnosis;
    emit textDiagnosisChanged(_textDiagnosis);
}

void AnamnesManager::unsetTextDiagnosis()
{
    _textDiagnosis.clear();
    emit textDiagnosisChanged(_textDiagnosis);
}

QString AnamnesManager::textByComplaint() const
{
    return _textByComplaint;
}

void AnamnesManager::setTextByComplaint(const QString &textByComplaint)
{
    _textByComplaint = textByComplaint;
    emit textByComplaintChanged(_textByComplaint);
}

void AnamnesManager::unsetTextByComplaint()
{
    _textByComplaint.clear();
    emit textByComplaintChanged(_textByComplaint);
}

QString AnamnesManager::textByAnamnes() const
{
    return _textByAnamnes;
}

void AnamnesManager::setTextByAnamnes(const QString &textByAnamnes)
{
    _textByAnamnes = textByAnamnes;
    emit textByAnamnesChanged(_textByAnamnes);
}

void AnamnesManager::unsetTextByAnamnes()
{
    _textByAnamnes.clear();
    emit textByAnamnesChanged(_textByAnamnes);
}

QString AnamnesManager::textPlanRes() const
{
    return _textPlanRes;
}

void AnamnesManager::setTextPlanRes(const QString &textPlanRes)
{
    _textPlanRes = textPlanRes;
    emit textPlanResChanged(_textPlanRes);
}

void AnamnesManager::unsetTextPlanRes()
{
    _textPlanRes.clear();
    emit textPlanResChanged(_textPlanRes);
}

QString AnamnesManager::textPlanTher() const
{
    return _textPlanTher;
}

void AnamnesManager::setTextPlanTher(const QString &textPlanTher)
{
    _textPlanTher = textPlanTher;
    emit textPlanTherChanged(_textPlanTher);
}

void AnamnesManager::unsetTextPlanTher()
{
    _textPlanTher.clear();
    emit textPlanTherChanged(_textPlanTher);
}

QString AnamnesManager::lineIncapacitated() const
{
    return _lineIncapacitated;
}

void AnamnesManager::setLineIncapacitated(const QString &lineIncapacitated)
{
    _lineIncapacitated = lineIncapacitated;
    emit lineIncapacitatedChanged(_lineIncapacitated);
}

void AnamnesManager::unsetLineIncapacitated()
{
    _lineIncapacitated.clear();
    emit lineIncapacitatedChanged(_lineIncapacitated);
}

QString AnamnesManager::lineDoc() const
{
    return _lineDoc;
}

void AnamnesManager::setLineDoc(const QString &lineDoc)
{
    _lineDoc = lineDoc;
    emit lineDocChanged(_lineDoc);
}

void AnamnesManager::unsetLineDoc()
{
    _lineDoc.clear();
    emit lineDocChanged(_lineDoc);
}

