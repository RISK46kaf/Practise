#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QObject>

namespace Core {

class ProfileManager : public QObject
{
    Q_OBJECT
public:
    explicit ProfileManager(QObject *parent = 0);

private:
    QString _lineMedCardID;
    QString _linePSRN;
    QString _lineMedComID;
    QString _lineMedValID;
    QString _lineSnilsID;
    QString _lineSale;
    QString _textSale;
    QString _lineName;
    QString _dateBth;
    bool _sex;
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

public slots:
    QString lineMedCardID() const;
    void setLineMedCardID(const QString& id);
    QString linePSRN() const;
    void setLinePSRN(const QString& psrn);
    QString lineMedComID() const;
    void setLineMedComID(const QString& id);
    QString lineMedValID() const;
    void setLineMedValID(const QString& id);
    QString lineSnilsID() const;
    void setLineSnilsID(const QString& id);
    QString lineSale() const;
    void setLineSale(const QString& sale);
    QString textSale() const;
    void setTextSale(const QString& text);
    QString lineName() const;
    void setLineName(const QString& name);
    QString dateBth() const;
    void setDateBth(const QString& data);
    bool sex() const;
    void setSex(bool sex);
    QString lineRegR() const;
    void setLineRegR(const QString& lineRegR);
    QString lineDistrR() const;
    void setLineDistrR(const QString& lineDistrR);
    QString lineLocR() const;
    void setLineLocR(const QString& lineLocR);
    QString lineStrR() const;
    void setLineStrR(const QString& lineStrR);
    QString lineHomR() const;
    void setLineHomR(const QString& lineHomR);
    QString lineBuilR() const;
    void setLineBuilR(const QString& lineBuilR);
    QString lineApR() const;
    void setLineApR(const QString& lineApR);
    QString lineRegC() const;
    void setLineRegC(const QString& lineRegC);
    QString lineDistrC() const;
    void setLineDistrC(const QString& lineDistrC);
    QString lineLocC() const;
    void setLineLocC(const QString& lineLocC);
    QString lineStrC() const;
    void setLineStrC(const QString& lineStrC);
    QString lineHomC() const;
    void setLineHomC(const QString& lineHomC);
    QString lineBuilC() const;
    void setLineBuilC(const QString& lineBuilC);
    QString lineApC() const;
    void setLineApC(const QString& lineApC);
};

}
#endif // PROFILEMANAGER_H
