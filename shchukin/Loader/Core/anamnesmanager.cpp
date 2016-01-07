#include "anamnesmanager.h"

using namespace Core;

AnamnesManager::AnamnesManager(QObject *parent) : QObject(parent)
{

}

QString AnamnesManager::dateSince() const
{
    return _dateSince;
}

void AnamnesManager::setDateSince(const QString &dateSince)
{
    _dateSince = dateSince;
}

QString AnamnesManager::textComplaint() const
{
    return _textComplaint;
}

void AnamnesManager::setTextComplaint(const QString &textComplaint)
{
    _textComplaint = textComplaint;
}

QString AnamnesManager::textAnDis() const
{
    return _textAnDis;
}

void AnamnesManager::setTextAnDis(const QString &textAnDis)
{
    _textAnDis = textAnDis;
}

QString AnamnesManager::textAnLi() const
{
    return _textAnLi;
}

void AnamnesManager::setTextAnLi(const QString &textAnLi)
{
    _textAnLi = textAnLi;
}

QString AnamnesManager::lineVen() const
{
    return _lineVen;
}

void AnamnesManager::setLineVen(const QString &lineVen)
{
    _lineVen = lineVen;
}

QString AnamnesManager::lineAler() const
{
    return _lineAler;
}

void AnamnesManager::setLineAler(const QString &lineAler)
{
    _lineAler = lineAler;
}

bool AnamnesManager::isCheckNorSt() const
{
    return _checkNorSt;
}

void AnamnesManager::setCheckNorSt(bool checkNorSt)
{
    _checkNorSt = checkNorSt;
}

QString AnamnesManager::linePhys() const
{
    return _linePhys;
}

void AnamnesManager::setLinePhys(const QString &linePhys)
{
    _linePhys = linePhys;
}

QString AnamnesManager::lineFood() const
{
    return _lineFood;
}

void AnamnesManager::setLineFood(const QString &lineFood)
{
    _lineFood = lineFood;
}

QString AnamnesManager::lineSkin() const
{
    return _lineSkin;
}

void AnamnesManager::setLineSkin(const QString &lineSkin)
{
    _lineSkin = lineSkin;
}

QString AnamnesManager::lineOedema() const
{
    return _lineOedema;
}

void AnamnesManager::setLineOedema(const QString &lineOedema)
{
    _lineOedema = lineOedema;
}

QString AnamnesManager::textLimpha() const
{
    return _textLimpha;
}

void AnamnesManager::setTextLimpha(const QString &textLimpha)
{
    _textLimpha = textLimpha;
}

QString AnamnesManager::lineTempr() const
{
    return _lineTempr;
}

void AnamnesManager::setLineTempr(const QString &lineTempr)
{
    _lineTempr = lineTempr;
}

QString AnamnesManager::lineRespR() const
{
    return _lineRespR;
}

void AnamnesManager::setLineRespR(const QString &lineRespR)
{
    _lineRespR = lineRespR;
}

QString AnamnesManager::lineThorax() const
{
    return _lineThorax;
}

void AnamnesManager::setLineThorax(const QString &lineThorax)
{
    _lineThorax = lineThorax;
}

QString AnamnesManager::linePercussion() const
{
    return _linePercussion;
}

void AnamnesManager::setLinePercussion(const QString &linePercussion)
{
    _linePercussion = linePercussion;
}

QString AnamnesManager::textBreath() const
{
    return _textBreath;
}

void AnamnesManager::setTextBreath(const QString &textBreath)
{
    _textBreath = textBreath;
}

QString AnamnesManager::lineHeartBorders() const
{
    return _lineHeartBorders;
}

void AnamnesManager::setLineHeartBorders(const QString &lineHeartBorders)
{
    _lineHeartBorders = lineHeartBorders;
}

QString AnamnesManager::lineSoniCordis() const
{
    return _lineSoniCordis;
}

void AnamnesManager::setLineSoniCordis(const QString &lineSoniCordis)
{
    _lineSoniCordis = lineSoniCordis;
}

QString AnamnesManager::lineArtPre() const
{
    return _lineArtPre;
}

void AnamnesManager::setLineArtPre(const QString &lineArtPre)
{
    _lineArtPre = lineArtPre;
}

QString AnamnesManager::linePulse() const
{
    return _linePulse;
}

void AnamnesManager::setLinePulse(const QString linePulse)
{
    _linePulse = linePulse;
}

QString AnamnesManager::linePulse2() const
{
    return _linePulse2;
}

void AnamnesManager::setLinePulse2(const QString linePulse2)
{
    _linePulse2 = linePulse2;
}

QString AnamnesManager::lineTongue() const
{
    return _lineTongue;
}

void AnamnesManager::setLineTongue(const QString &lineTongue)
{
    _lineTongue = lineTongue;
}

QString AnamnesManager::textStomach() const
{
    return _textStomach;
}

void AnamnesManager::setTextStomach(const QString &textStomach)
{
    _textStomach = textStomach;
}

QString AnamnesManager::textLiver() const
{
    return _textLiver;
}

void AnamnesManager::setTextLiver(const QString &textLiver)
{
    _textLiver = textLiver;
}

QString AnamnesManager::textPasternatsky() const
{
    return _textPasternatsky;
}

void AnamnesManager::setTextPasternatsky(const QString &textPasternatsky)
{
    _textPasternatsky = textPasternatsky;
}

QString AnamnesManager::lineFeces() const
{
    return _lineFeces;
}

void AnamnesManager::setLineFeces(const QString &lineFeces)
{
    _lineFeces = lineFeces;
}

QString AnamnesManager::textUrination() const
{
    return _textUrination;
}

void AnamnesManager::setTextUrination(const QString &textUrination)
{
    _textUrination = textUrination;
}

QString AnamnesManager::textDiagnosis() const
{
    return _textDiagnosis;
}

void AnamnesManager::setTextDiagnosis(const QString &textDiagnosis)
{
    _textDiagnosis = textDiagnosis;
}

QString AnamnesManager::textByComplaint() const
{
    return _textByComplaint;
}

void AnamnesManager::setTextByComplaint(const QString &textByComplaint)
{
    _textByComplaint = textByComplaint;
}

QString AnamnesManager::textByAnamnes() const
{
    return _textByAnamnes;
}

void AnamnesManager::setTextByAnamnes(const QString &textByAnamnes)
{
    _textByAnamnes = textByAnamnes;
}

QString AnamnesManager::textPlanRes() const
{
    return _textPlanRes;
}

void AnamnesManager::setTextPlanRes(const QString &textPlanRes)
{
    _textPlanRes = textPlanRes;
}

QString AnamnesManager::textPlanTher() const
{
    return _textPlanTher;
}

void AnamnesManager::setTextPlanTher(const QString &textPlanTher)
{
    _textPlanTher = textPlanTher;
}

QString AnamnesManager::lineIncapacitated() const
{
    return _lineIncapacitated;
}

void AnamnesManager::setLineIncapacitated(const QString &lineIncapacitated)
{
    _lineIncapacitated = lineIncapacitated;
}

QString AnamnesManager::lineDoc() const
{
    return _lineDoc;
}

void AnamnesManager::setLineDoc(const QString &lineDoc)
{
    _lineDoc = lineDoc;
}

