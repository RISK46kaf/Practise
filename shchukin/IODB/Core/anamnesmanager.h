#ifndef ANAMNESMANAGER_H
#define ANAMNESMANAGER_H

#include <QObject>
#include <QDate>

namespace Core {

class AnamnesManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate dateSince READ dateSince WRITE setDateSince
               RESET unsetDateSince NOTIFY dateSinceChanged)
    Q_PROPERTY(QString textComplaint READ textComplaint WRITE setTextComplaint
               RESET unsetTextComplaint NOTIFY textComplaintChanged)
    Q_PROPERTY(QString textAnDis READ textAnDis WRITE setTextAnDis
               RESET unsetTextAnDis NOTIFY textAnDisChanged)
    Q_PROPERTY(QString textAnLi READ textAnLi WRITE setTextAnLi
               RESET unsetTextAnLi NOTIFY textAnLiChanged)
    Q_PROPERTY(QString lineVen READ lineVen WRITE setLineVen
               RESET unsetLineVen NOTIFY lineVenChanged)
    Q_PROPERTY(QString lineAler READ lineAler WRITE setLineAler
               RESET unsetLineAler NOTIFY lineAlerChanged)
    Q_PROPERTY(bool checkNorSt READ isCheckNorSt WRITE setCheckNorSt
               RESET unsetCheckNorSt NOTIFY checkNorStChanged)
    Q_PROPERTY(QString linePhys READ linePhys WRITE setLinePhys
               RESET unsetLinePhys NOTIFY linePhysChanged)
    Q_PROPERTY(QString lineFood READ lineFood WRITE setLineFood
               RESET unsetLineFood NOTIFY lineFoodChanged)
    Q_PROPERTY(QString lineSkin READ lineSkin WRITE setLineSkin
               RESET unsetLineSkin NOTIFY lineSkinChanged)
    Q_PROPERTY(QString lineOedema READ lineOedema WRITE setLineOedema
               RESET unsetLineOedema NOTIFY lineOedemaChanged)
    Q_PROPERTY(QString textLimpha READ textLimpha WRITE setTextLimpha
               RESET unsetTextLimpha NOTIFY textLimphaChanged)
    Q_PROPERTY(QString lineTempr READ lineTempr WRITE setLineTempr
               RESET unsetLineTempr NOTIFY lineTemprChanged)
    Q_PROPERTY(QString lineRespR READ lineRespR WRITE setLineRespR
               RESET unsetLineRespR NOTIFY lineRespRChanged)
    Q_PROPERTY(QString lineThorax READ lineThorax WRITE setLineThorax
               RESET unsetLineThorax NOTIFY lineThoraxChanged)
    Q_PROPERTY(QString linePercussion READ linePercussion WRITE setLinePercussion
               RESET unsetLinePercussion NOTIFY linePercussionChanged)
    Q_PROPERTY(QString textBreath READ textBreath WRITE setTextBreath
               RESET unsetTextBreath NOTIFY textBreathChanged)
    Q_PROPERTY(QString lineHeartBorders READ lineHeartBorders WRITE setLineHeartBorders
               RESET unsetLineHeartBorders NOTIFY lineHeartBordersChanged)
    Q_PROPERTY(QString lineSoniCordis READ lineSoniCordis WRITE setLineSoniCordis
               RESET unsetLineSoniCordis NOTIFY lineSoniCordisChanged)
    Q_PROPERTY(QString lineArtPre READ lineArtPre WRITE setLineArtPre
               RESET unsetLineArtPre NOTIFY lineArtPreChanged)
    Q_PROPERTY(QString linePulse READ linePulse WRITE setLinePulse
               RESET unsetLinePulse NOTIFY linePulseChanged)
    Q_PROPERTY(QString linePulse2 READ linePulse2 WRITE setLinePulse2
               RESET unsetLinePulse2 NOTIFY linePulse2Changed)
    Q_PROPERTY(QString lineTongue READ lineTongue WRITE setLineTongue
               RESET unsetLineTongue NOTIFY lineTongueChanged)
    Q_PROPERTY(QString textStomach READ textStomach WRITE setTextStomach
               RESET unsetTextStomach NOTIFY textStomachChanged)
    Q_PROPERTY(QString textLiver READ textLiver WRITE setTextLiver
               RESET unsetTextLiver NOTIFY textLiverChanged)
    Q_PROPERTY(QString textPasternatsky READ textPasternatsky WRITE setTextPasternatsky
               RESET unsetTextPasternatsky NOTIFY textPasternatskyChanged)
    Q_PROPERTY(QString lineFeces READ lineFeces WRITE setLineFeces
               RESET unsetLineFeces NOTIFY lineFecesChanged)
    Q_PROPERTY(QString textUrination READ textUrination WRITE setTextUrination
               RESET unsetTextUrination NOTIFY textUrinationChanged)
    Q_PROPERTY(QString textDiagnosis READ textDiagnosis WRITE setTextDiagnosis
               RESET unsetTextDiagnosis NOTIFY textDiagnosisChanged)
    Q_PROPERTY(QString textByComplaint READ textByComplaint WRITE setTextByComplaint
               RESET unsetTextByComplaint NOTIFY textByComplaintChanged)
    Q_PROPERTY(QString textByAnamnes READ textByAnamnes WRITE setTextByAnamnes
               RESET unsetTextByAnamnes NOTIFY textByAnamnesChanged)
    Q_PROPERTY(QString textPlanRes READ textPlanRes WRITE setTextPlanRes
               RESET unsetTextPlanRes NOTIFY textPlanResChanged)
    Q_PROPERTY(QString textPlanTher READ textPlanTher WRITE setTextPlanTher
               RESET unsetTextPlanTher NOTIFY textPlanTherChanged)
    Q_PROPERTY(QString lineIncapacitated READ lineIncapacitated WRITE setLineIncapacitated
               RESET unsetLineIncapacitated NOTIFY lineIncapacitatedChanged)
    Q_PROPERTY(QString lineDoc READ lineDoc WRITE setLineDoc
               RESET unsetLineDoc NOTIFY lineDocChanged)

public:
    Q_INVOKABLE
    explicit AnamnesManager(QObject *parent = 0);
    AnamnesManager(const AnamnesManager& other);
    AnamnesManager& operator=(const AnamnesManager& other);

    QDate dateSince() const;
    QString textComplaint() const;
    QString textAnDis() const;
    QString textAnLi() const;
    QString lineVen() const;
    QString lineAler() const;
    bool isCheckNorSt() const;
    QString linePhys() const;
    QString lineFood() const;
    QString lineSkin() const;
    QString lineOedema() const;
    QString textLimpha() const;
    QString lineTempr() const;
    QString lineRespR() const;
    QString lineThorax() const;
    QString linePercussion() const;
    QString textBreath() const;
    QString lineHeartBorders() const;
    QString lineSoniCordis() const;
    QString lineArtPre() const;
    QString linePulse() const;
    QString linePulse2() const;
    QString lineTongue() const;
    QString textStomach() const;
    QString textLiver() const;
    QString textPasternatsky() const;
    QString lineFeces() const;
    QString textUrination() const;
    QString textDiagnosis() const;
    QString textByComplaint() const;
    QString textByAnamnes() const;
    QString textPlanRes() const;
    QString textPlanTher() const;
    QString lineIncapacitated() const;
    QString lineDoc() const;
private:
    QDate _dateSince;
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
    void dateSinceChanged(QDate);
    void textComplaintChanged(QString);
    void textAnDisChanged(QString);
    void textAnLiChanged(QString);
    void lineVenChanged(QString);
    void lineAlerChanged(QString);
    void checkNorStChanged(bool);
    void linePhysChanged(QString);
    void lineFoodChanged(QString);
    void lineSkinChanged(QString);
    void lineOedemaChanged(QString);
    void textLimphaChanged(QString);
    void lineTemprChanged(QString);
    void lineRespRChanged(QString);
    void lineThoraxChanged(QString);
    void linePercussionChanged(QString);
    void textBreathChanged(QString);
    void lineHeartBordersChanged(QString);
    void lineSoniCordisChanged(QString);
    void lineArtPreChanged(QString);
    void linePulseChanged(QString);
    void linePulse2Changed(QString);
    void lineTongueChanged(QString);
    void textStomachChanged(QString);
    void textLiverChanged(QString);
    void textPasternatskyChanged(QString);
    void lineFecesChanged(QString);
    void textUrinationChanged(QString);
    void textDiagnosisChanged(QString);
    void textByComplaintChanged(QString);
    void textByAnamnesChanged(QString);
    void textPlanResChanged(QString);
    void textPlanTherChanged(QString);
    void lineIncapacitatedChanged(QString);
    void lineDocChanged(QString);

public slots:
    void resetAll();
    void setDateSince(const QDate& dateSince);
    void unsetDateSince();
    void setTextComplaint(const QString& textComplaint);
    void unsetTextComplaint();
    void setTextAnDis(const QString& textAnDis);
    void unsetTextAnDis();
    void setTextAnLi(const QString& textAnLi);
    void unsetTextAnLi();
    void setLineVen(const QString& lineVen);
    void unsetLineVen();
    void setLineAler(const QString& lineAler);
    void unsetLineAler();
    void setCheckNorSt(bool checkNorSt);
    void unsetCheckNorSt();
    void setLinePhys(const QString& linePhys);
    void unsetLinePhys();
    void setLineFood(const QString& lineFood);
    void unsetLineFood();
    void setLineSkin(const QString& lineSkin);
    void unsetLineSkin();
    void setLineOedema(const QString& lineOedema);
    void unsetLineOedema();
    void setTextLimpha(const QString& textLimpha);
    void unsetTextLimpha();
    void setLineTempr(const QString& lineTempr);
    void unsetLineTempr();
    void setLineRespR(const QString& lineRespR);
    void unsetLineRespR();
    void setLineThorax(const QString& lineThorax);
    void unsetLineThorax();
    void setLinePercussion(const QString& linePercussion);
    void unsetLinePercussion();
    void setTextBreath(const QString& textBreath);
    void unsetTextBreath();
    void setLineHeartBorders(const QString& lineHeartBorders);
    void unsetLineHeartBorders();
    void setLineSoniCordis(const QString& lineSoniCordis);
    void unsetLineSoniCordis();
    void setLineArtPre(const QString& lineArtPre);
    void unsetLineArtPre();
    void setLinePulse(const QString linePulse);
    void unsetLinePulse();
    void setLinePulse2(const QString linePulse2);
    void unsetLinePulse2();
    void setLineTongue(const QString& lineTongue);
    void unsetLineTongue();
    void setTextStomach(const QString& textStomach);
    void unsetTextStomach();
    void setTextLiver(const QString& textLiver);
    void unsetTextLiver();
    void setTextPasternatsky(const QString& textPasternatsky);
    void unsetTextPasternatsky();
    void setLineFeces(const QString& lineFeces);
    void unsetLineFeces();
    void setTextUrination(const QString& textUrination);
    void unsetTextUrination();
    void setTextDiagnosis(const QString& textDiagnosis);
    void unsetTextDiagnosis();
    void setTextByComplaint(const QString& textByComplaint);
    void unsetTextByComplaint();
    void setTextByAnamnes(const QString& textByAnamnes);
    void unsetTextByAnamnes();
    void setTextPlanRes(const QString& textPlanRes);
    void unsetTextPlanRes();
    void setTextPlanTher(const QString& textPlanTher);
    void unsetTextPlanTher();
    void setLineIncapacitated(const QString& lineIncapacitated);
    void unsetLineIncapacitated();
    void setLineDoc(const QString& lineDoc);
    void unsetLineDoc();

};

} // namespace Core

Q_DECLARE_METATYPE(Core::AnamnesManager)

#endif // ANAMNESMANAGER_H
