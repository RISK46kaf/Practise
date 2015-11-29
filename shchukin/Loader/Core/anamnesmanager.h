#ifndef ANAMNESMANAGER_H
#define ANAMNESMANAGER_H

#include <QObject>

namespace Core {

class AnamnesManager : public QObject
{
    Q_OBJECT
public:
    explicit AnamnesManager(QObject *parent = 0);

private:
    QString _dateSince;
    QString _textComplaint;
    QString _textAnDis;
    QString _textAnLi;
    QString _lineVen;
    QString _lineAler;
    bool _checkNorSt;
    QString _linePhys;
    QString _lineFood;
    QString _lineSkin;
    QString _lineOedema;
    QString _textLimpha;
    QString _lineTempr;
    QString _lineRespR;
    QString _lineThorax;
    QString _linePercussion;
    QString _textBreath;
    QString _lineHeartBorders;
    QString _lineSoniCordis;
    QString _lineArtPre;
    QString _linePulse;
    QString _linePulse2;
    QString _lineTongue;
    QString _textStomach;
    QString _textLiver;
    QString _textPasternatsky;
    QString _lineFeces;
    QString _textUrination;
    QString _textDiagnosis;
    QString _textByComplaint;
    QString _textByAnamnes;
    QString _textPlanRes;
    QString _textPlanTher;
    QString _lineIncapacitated;
    QString _lineDoc;

signals:

public slots:
    QString dateSince() const;
    void setDateSince(const QString& dateSince);
    QString textComplaint() const;
    void setTextComplaint(const QString& textComplaint);
    QString textAnDis() const;
    void setTextAnDis(const QString& textAnDis);
    QString textAnLi() const;
    void setTextAnLi(const QString& textAnLi);
    QString lineVen() const;
    void setLineVen(const QString& lineVen);
    QString lineAler() const;
    void setLineAler(const QString& lineAler);
    bool isCheckNorSt() const;
    void setCheckNorSt(bool checkNorSt);
    QString linePhys() const;
    void setLinePhys(const QString& linePhys);
    QString lineFood() const;
    void setLineFood(const QString& lineFood);
    QString lineSkin() const;
    void setLineSkin(const QString& lineSkin);
    QString lineOedema() const;
    void setLineOedema(const QString& lineOedema);
    QString textLimpha() const;
    void setTextLimpha(const QString& textLimpha);
    QString lineTempr() const;
    void setLineTempr(const QString& lineTempr);
    QString lineRespR() const;
    void setLineRespR(const QString& lineRespR);
    QString lineThorax() const;
    void setLineThorax(const QString& lineThorax);
    QString linePercussion() const;
    void setLinePercussion(const QString& linePercussion);
    QString textBreath() const;
    void setTextBreath(const QString& textBreath);
    QString lineHeartBorders() const;
    void setLineHeartBorders(const QString& lineHeartBorders);
    QString lineSoniCordis() const;
    void setLineSoniCordis(const QString& lineSoniCordis);
    QString lineArtPre() const;
    void setLineArtPre(const QString& lineArtPre);
    QString linePulse() const;
    void setLinePulse(const QString linePulse);
    QString linePulse2() const;
    void setLinePulse2(const QString linePulse2);
    QString lineTongue() const;
    void setLineTongue(const QString& lineTongue);
    QString textStomach() const;
    void setTextStomach(const QString& textStomach);
    QString textLiver() const;
    void setTextLiver(const QString& textLiver);
    QString textPasternatsky() const;
    void setTextPasternatsky(const QString& textPasternatsky);
    QString lineFeces() const;
    void setLineFeces(const QString& lineFeces);
    QString textUrination() const;
    void setTextUrination(const QString& textUrination);
    QString textDiagnosis() const;
    void setTextDiagnosis(const QString& textDiagnosis);
    QString textByComplaint() const;
    void setTextByComplaint(const QString& textByComplaint);
    QString textByAnamnes() const;
    void setTextByAnamnes(const QString& textByAnamnes);
    QString textPlanRes() const;
    void setTextPlanRes(const QString& textPlanRes);
    QString textPlanTher() const;
    void setTextPlanTher(const QString& textPlanTher);
    QString lineIncapacitated() const;
    void setLineIncapacitated(const QString& lineIncapacitated);
    QString lineDoc() const;
    void setLineDoc(const QString& lineDoc);

};

}
#endif // ANAMNESMANAGER_H
