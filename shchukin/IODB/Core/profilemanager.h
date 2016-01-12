#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QObject>
#include <QDate>

namespace Core {

class ProfileManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString lineMedCardID READ lineMedCardID WRITE setLineMedCardID
               RESET unsetLineMedCardID  NOTIFY lineMedCardIDChanged)
    Q_PROPERTY(QString linePSRN READ linePSRN WRITE setLinePSRN
               RESET unsetLinePSRN NOTIFY linePSRNChanged)
    Q_PROPERTY(QString lineMedComID READ lineMedComID WRITE setLineMedComID
               RESET unsetLineMedComID NOTIFY lineMedComIDChanged)
    Q_PROPERTY(QString lineMedValID READ lineMedValID WRITE setLineMedValID
               RESET unsetLineMedValID NOTIFY lineMedValIDChanged)
    Q_PROPERTY(QString lineSnilsID READ lineSnilsID WRITE setLineSnilsID
               RESET unsetLineSnilsID NOTIFY lineSnilsIDChanged)
    Q_PROPERTY(QString lineSale READ lineSale WRITE setLineSale
               RESET unsetLineSale NOTIFY lineSaleChanged)
    Q_PROPERTY(QString textSale READ textSale WRITE setTextSale
               RESET unsetTextSale NOTIFY textSaleChanged)
    Q_PROPERTY(QString lineName READ lineName WRITE setLineName
               RESET unsetLineName NOTIFY lineNameChanged)
    Q_PROPERTY(QDate dateBth READ dateBth WRITE setDateBth
               RESET unsetDateBth NOTIFY dateBthChanged)
    Q_PROPERTY(bool sex READ sex WRITE setSex
               RESET unsetSex  NOTIFY sexChanged)
    Q_PROPERTY(QString lineDiagnL READ lineDiagnL WRITE setLineDiagnL
               RESET unsetLineDiagnL  NOTIFY lineDiagnLChanged)
    Q_PROPERTY(QString lineRegR READ lineRegR WRITE setLineRegR
               RESET unsetLineRegR NOTIFY lineRegRChanged)
    Q_PROPERTY(QString lineDistrR READ lineDistrR WRITE setLineDistrR
               RESET unsetLineDistrR NOTIFY lineDistrRChanged)
    Q_PROPERTY(QString lineLocR READ lineLocR WRITE setLineLocR
               RESET unsetLineLocR NOTIFY lineLocRChanged)
    Q_PROPERTY(QString lineStrR READ lineStrR WRITE setLineStrR
               RESET unsetLineStrR NOTIFY lineStrRChanged)
    Q_PROPERTY(QString lineHomR READ lineHomR WRITE setLineHomR
               RESET unsetLineHomR NOTIFY lineHomRChanged)
    Q_PROPERTY(QString lineBuilR READ lineBuilR WRITE setLineBuilR
               RESET unsetLineBuilR NOTIFY lineBuilRChanged)
    Q_PROPERTY(QString lineApR READ lineApR WRITE setLineApR
               RESET unsetLineApR NOTIFY lineApRChanged)
    Q_PROPERTY(QString lineRegC READ lineRegC WRITE setLineRegC
               RESET unsetLineRegC NOTIFY lineRegCChanged)
    Q_PROPERTY(QString lineDistrC READ lineDistrC WRITE setLineDistrC
               RESET unsetLineDistrC NOTIFY lineDistrCChanged)
    Q_PROPERTY(QString lineLocC READ lineLocC WRITE setLineLocC
               RESET unsetLineLocC NOTIFY lineLocCChanged)
    Q_PROPERTY(QString lineStrC READ lineStrC WRITE setLineStrC
               RESET unsetLineStrC NOTIFY lineStrCChanged)
    Q_PROPERTY(QString lineHomC READ lineHomC WRITE setLineHomC
               RESET unsetLineHomC NOTIFY lineHomCChanged)
    Q_PROPERTY(QString lineBuilC READ lineBuilC WRITE setLineBuilC
               RESET unsetLineBuilC NOTIFY lineBuilCChanged)
    Q_PROPERTY(QString lineApC READ lineApC WRITE setLineApC
               RESET unsetLineApC NOTIFY lineApCChanged)

public:
    Q_INVOKABLE
    explicit ProfileManager(QObject *parent = 0);
    ProfileManager(const ProfileManager& other);
    ProfileManager& operator=(const ProfileManager& other);
    QString lineMedCardID() const;
    QString linePSRN() const;
    QString lineMedComID() const;
    QString lineMedValID() const;
    QString lineSnilsID() const;
    QString lineSale() const;
    QString textSale() const;
    QString lineName() const;
    QDate dateBth() const;
    bool sex() const;
    QString lineDiagnL() const;
    QString lineRegR() const;
    QString lineDistrR() const;
    QString lineLocR() const;
    QString lineStrR() const;
    QString lineHomR() const;
    QString lineBuilR() const;
    QString lineApR() const;
    QString lineRegC() const;
    QString lineDistrC() const;
    QString lineLocC() const;
    QString lineStrC() const;
    QString lineHomC() const;
    QString lineBuilC() const;
    QString lineApC() const;

private:
    QString _lineMedCardID;
    QString _linePSRN;
    QString _lineMedComID;
    QString _lineMedValID;
    QString _lineSnilsID;
    QString _lineSale;
    QString _textSale;
    QString _lineName;
    QDate _dateBth;
    bool _sex;
    QString _lineDiagnL;
    QString _lineRegR;
    QString _lineDistrR;
    QString _lineLocR;
    QString _lineStrR;
    QString _lineHomR;
    QString _lineBuilR;
    QString _lineApR;
    QString _lineRegC;
    QString _lineDistrC;
    QString _lineLocC;
    QString _lineStrC;
    QString _lineHomC;
    QString _lineBuilC;
    QString _lineApC;
signals:
    void lineMedCardIDChanged(QString);
    void linePSRNChanged(QString);
    void lineMedComIDChanged(QString);
    void lineMedValIDChanged(QString);
    void lineSnilsIDChanged(QString);
    void lineSaleChanged(QString);
    void textSaleChanged(QString);
    void lineNameChanged(QString);
    void dateBthChanged(QDate);
    void sexChanged(bool);
    void lineDiagnLChanged(QString);
    void lineRegRChanged(QString);
    void lineDistrRChanged(QString);
    void lineLocRChanged(QString);
    void lineStrRChanged(QString);
    void lineHomRChanged(QString);
    void lineBuilRChanged(QString);
    void lineApRChanged(QString);
    void lineRegCChanged(QString);
    void lineDistrCChanged(QString);
    void lineLocCChanged(QString);
    void lineStrCChanged(QString);
    void lineHomCChanged(QString);
    void lineBuilCChanged(QString);
    void lineApCChanged(QString);
public slots:
    void resetAll();
    void setLineMedCardID(const QString& id);
    void unsetLineMedCardID();
    void setLinePSRN(const QString& psrn);
    void unsetLinePSRN();
    void setLineMedComID(const QString& id);
    void unsetLineMedComID();
    void setLineMedValID(const QString& id);
    void unsetLineMedValID();
    void setLineSnilsID(const QString& id);
    void unsetLineSnilsID();
    void setLineSale(const QString& sale);
    void unsetLineSale();
    void setTextSale(const QString& text);
    void unsetTextSale();
    void setLineName(const QString& name);
    void unsetLineName();
    void setDateBth(const QDate& data);
    void unsetDateBth();
    void setSex(bool sex);
    void unsetSex();
    void setLineDiagnL(const QString& lineDiagnL);
    void unsetLineDiagnL();
    void setLineRegR(const QString& lineRegR);
    void unsetLineRegR();
    void setLineDistrR(const QString& lineDistrR);
    void unsetLineDistrR();
    void setLineLocR(const QString& lineLocR);
    void unsetLineLocR();
    void setLineStrR(const QString& lineStrR);
    void unsetLineStrR();
    void setLineHomR(const QString& lineHomR);
    void unsetLineHomR();
    void setLineBuilR(const QString& lineBuilR);
    void unsetLineBuilR();
    void setLineApR(const QString& lineApR);
    void unsetLineApR();
    void setLineRegC(const QString& lineRegC);
    void unsetLineRegC();
    void setLineDistrC(const QString& lineDistrC);
    void unsetLineDistrC();
    void setLineLocC(const QString& lineLocC);
    void unsetLineLocC();
    void setLineStrC(const QString& lineStrC);
    void unsetLineStrC();
    void setLineHomC(const QString& lineHomC);
    void unsetLineHomC();
    void setLineBuilC(const QString& lineBuilC);
    void unsetLineBuilC();
    void setLineApC(const QString& lineApC);
    void unsetLineApC();
};
} // namespace Core
Q_DECLARE_METATYPE(Core::ProfileManager)
#endif // PROFILEMANAGER_H
