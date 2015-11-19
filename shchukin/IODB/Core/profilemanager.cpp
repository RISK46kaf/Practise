#include "profilemanager.h"
#include <QMetaProperty>
#include <QDebug>

using namespace Core;

ProfileManager::ProfileManager(QObject *parent) : QObject(parent)
{
    setObjectName("ProfileManager");
    resetAll();
}

ProfileManager::ProfileManager(const ProfileManager &other)
{
    _lineMedCardID = other._lineMedCardID;
    _linePSRN = other._linePSRN;
    _lineMedComID = other._lineMedComID;
    _lineMedValID = other._lineMedValID;
    _lineSnilsID = other._lineSnilsID;
    _lineSale = other._lineSale;
    _textSale = other._textSale;
    _lineName = other._lineName;
    _dateBth = other._dateBth;
    _sex = other._sex;
    _lineRegR = other._lineRegR;
    _lineDistrR = other._lineDistrR;
    _lineLocR = other._lineLocR;
    _lineStrR = other._lineStrR;
    _lineHomR = other._lineHomR;
    _lineBuilR = other._lineBuilR;
    _lineApR = other._lineApR;
    _lineRegC = other._lineRegC;
    _lineDistrC = other._lineDistrC;
    _lineLocC = other._lineLocC;
    _lineStrC = other._lineStrC;
    _lineHomC = other._lineHomC;
    _lineBuilC = other._lineBuilC;
    _lineApC = other._lineApC;
}

ProfileManager &ProfileManager::operator=(const ProfileManager &other)
{
    _lineMedCardID = other._lineMedCardID;
    _linePSRN = other._linePSRN;
    _lineMedComID = other._lineMedComID;
    _lineMedValID = other._lineMedValID;
    _lineSnilsID = other._lineSnilsID;
    _lineSale = other._lineSale;
    _textSale = other._textSale;
    _lineName = other._lineName;
    _dateBth = other._dateBth;
    _sex = other._sex;
    _lineRegR = other._lineRegR;
    _lineDistrR = other._lineDistrR;
    _lineLocR = other._lineLocR;
    _lineStrR = other._lineStrR;
    _lineHomR = other._lineHomR;
    _lineBuilR = other._lineBuilR;
    _lineApR = other._lineApR;
    _lineRegC = other._lineRegC;
    _lineDistrC = other._lineDistrC;
    _lineLocC = other._lineLocC;
    _lineStrC = other._lineStrC;
    _lineHomC = other._lineHomC;
    _lineBuilC = other._lineBuilC;
    _lineApC = other._lineApC;
    return (*this);
}

QString ProfileManager::lineMedCardID() const
{
    return _lineMedCardID;
}

void ProfileManager::setLineMedCardID(const QString &id)
{
    _lineMedCardID = id;
    lineMedCardIDChanged(_lineMedCardID);
}

void ProfileManager::unsetLineMedCardID()
{
    _lineMedCardID.clear();
    lineMedCardIDChanged(_lineMedCardID);
}

QString ProfileManager::linePSRN() const
{
    return _linePSRN;
}

void ProfileManager::setLinePSRN(const QString &psrn)
{
    _linePSRN = psrn;
    linePSRNChanged(_linePSRN);
}

void ProfileManager::unsetLinePSRN()
{
    _linePSRN.clear();
    linePSRNChanged(_linePSRN);
}

QString ProfileManager::lineMedComID() const
{
    return _lineMedComID;
}

void ProfileManager::setLineMedComID(const QString &id)
{
    _lineMedComID = id;
    lineMedComIDChanged(_lineMedComID);
}

void ProfileManager::unsetLineMedComID()
{
    _lineMedComID.clear();
    lineMedComIDChanged(_lineMedComID);
}

QString ProfileManager::lineMedValID() const
{
    return _lineMedValID;
}

void ProfileManager::setLineMedValID(const QString &id)
{
    _lineMedValID = id;
    lineMedValIDChanged(_lineMedValID);
}

void ProfileManager::unsetLineMedValID()
{
    _lineMedValID.clear();
    lineMedValIDChanged(_lineMedValID);
}

QString ProfileManager::lineSnilsID() const
{
    return _lineSnilsID;
}

void ProfileManager::setLineSnilsID(const QString &id)
{
    _lineSnilsID = id;
    lineSnilsIDChanged(_lineSnilsID);
}

void ProfileManager::unsetLineSnilsID()
{
    _lineSnilsID.clear();
    lineSnilsIDChanged(_lineSnilsID);
}

QString ProfileManager::lineSale() const
{
    return _lineSale;
}

void ProfileManager::setLineSale(const QString &sale)
{
    _lineSale = sale;
    lineSaleChanged(_lineSale);
}

void ProfileManager::unsetLineSale()
{
    _lineSale.clear();
    lineSaleChanged(_lineSale);
}

QString ProfileManager::textSale() const
{
    return _textSale;
}

void ProfileManager::setTextSale(const QString &text)
{
    _textSale = text;
    textSaleChanged(_textSale);
}

void ProfileManager::unsetTextSale()
{
    _textSale.clear();
    textSaleChanged(_textSale);
}

QString ProfileManager::lineName() const
{
    return _lineName;
}

void ProfileManager::setLineName(const QString &name)
{
    _lineName = name;
    lineNameChanged(_lineName);
}

void ProfileManager::unsetLineName()
{
    _lineName.clear();
    lineNameChanged(_lineName);
}

QDate ProfileManager::dateBth() const
{
    return _dateBth;
}

void ProfileManager::setDateBth(const QDate &data)
{
    _dateBth = data;
    dateBthChanged(_dateBth);
}

void ProfileManager::unsetDateBth()
{
    _dateBth = QDate::fromString("01.01.1902","dd.MM.yyyy");
    dateBthChanged(_dateBth);
}

bool ProfileManager::sex() const
{
    return _sex;
}

void ProfileManager::setSex(bool sex)
{
    _sex = sex;
    sexChanged(_sex);
}

void ProfileManager::unsetSex()
{
    _sex = true;
    sexChanged(_sex);
}

QString ProfileManager::lineRegR() const
{
    qDebug() << "isE" << _lineRegR.isEmpty();
    return _lineRegR;
}

void ProfileManager::setLineRegR(const QString &lineRegR)
{
    _lineRegR = lineRegR;
    lineRegRChanged(_lineRegR);
}

void ProfileManager::unsetLineRegR()
{
    _lineRegR.clear();
    lineRegRChanged(_lineRegR);
}

QString ProfileManager::lineDistrR() const
{
    return _lineDistrR;
}

void ProfileManager::setLineDistrR(const QString &lineDistrR)
{
    _lineDistrR = lineDistrR;
    lineDistrRChanged(_lineDistrR);
}

void ProfileManager::unsetLineDistrR()
{
    _lineDistrR.clear();
    lineDistrRChanged(_lineDistrR);
}

QString ProfileManager::lineLocR() const
{
    return _lineLocR;
}

void ProfileManager::setLineLocR(const QString &lineLocR)
{
    _lineLocR = lineLocR;
    lineLocRChanged(_lineLocR);
}

void ProfileManager::unsetLineLocR()
{
    _lineLocR.clear();
    lineLocRChanged(_lineLocR);
}

QString ProfileManager::lineStrR() const
{
    return _lineStrR;
}

void ProfileManager::setLineStrR(const QString &lineStrR)
{
    _lineStrR = lineStrR;
    lineStrRChanged(_lineStrR);
}

void ProfileManager::unsetLineStrR()
{
    _lineStrR.clear();
    lineStrRChanged(_lineStrR);
}

QString ProfileManager::lineHomR() const
{
    return _lineHomR;
}

void ProfileManager::setLineHomR(const QString &lineHomR)
{
    _lineHomR = lineHomR;
    lineHomRChanged(_lineHomR);
}

void ProfileManager::unsetLineHomR()
{
    _lineHomR.clear();
    lineHomRChanged(_lineHomR);
}

QString ProfileManager::lineBuilR() const
{
    return _lineBuilR;
}

void ProfileManager::setLineBuilR(const QString &lineBuilR)
{
    _lineBuilR = lineBuilR;
    lineBuilRChanged(_lineBuilR);
}

void ProfileManager::unsetLineBuilR()
{
    _lineBuilR.clear();
    lineBuilRChanged(_lineBuilR);
}

QString ProfileManager::lineApR() const
{
    return _lineApR;
}

void ProfileManager::setLineApR(const QString &lineApR)
{
    _lineApR = lineApR;
    lineApRChanged(_lineApR);
}

void ProfileManager::unsetLineApR()
{
    _lineApR.clear();
    lineApRChanged(_lineApR);
}

QString ProfileManager::lineRegC() const
{
    return _lineRegC;
}

void ProfileManager::setLineRegC(const QString &lineRegC)
{
    _lineRegC = lineRegC;
    lineRegCChanged(_lineRegC);
}

void ProfileManager::unsetLineRegC()
{
    _lineRegC.clear();
    lineRegCChanged(_lineRegC);
}

QString ProfileManager::lineDistrC() const
{
    return _lineDistrC;
}

void ProfileManager::setLineDistrC(const QString &lineDistrC)
{
    _lineDistrC = lineDistrC;
    lineDistrCChanged(_lineDistrC);
}

void ProfileManager::unsetLineDistrC()
{
    _lineDistrC.clear();
    lineDistrCChanged(_lineDistrC);
}

QString ProfileManager::lineLocC() const
{
    return _lineLocC;
}

void ProfileManager::setLineLocC(const QString &lineLocC)
{
    _lineLocC = lineLocC;
    lineLocCChanged(_lineLocC);
}

void ProfileManager::unsetLineLocC()
{
    _lineLocC.clear();
    lineLocCChanged(_lineLocC);
}

QString ProfileManager::lineStrC() const
{
    return _lineStrC;
}

void ProfileManager::setLineStrC(const QString &lineStrC)
{
    _lineStrC = lineStrC;
    lineStrCChanged(_lineStrC);
}

void ProfileManager::unsetLineStrC()
{
    _lineStrC.clear();
    lineStrCChanged(_lineStrC);
}

QString ProfileManager::lineHomC() const
{
    return _lineHomC;
}

void ProfileManager::setLineHomC(const QString &lineHomC)
{
    _lineHomC = lineHomC;
    lineHomCChanged(_lineHomC);
}

void ProfileManager::unsetLineHomC()
{
    _lineHomC.clear();
    lineHomCChanged(_lineHomC);
}

QString ProfileManager::lineBuilC() const
{
    return _lineBuilC;
}

void ProfileManager::setLineBuilC(const QString &lineBuilC)
{
    _lineBuilC = lineBuilC;
    lineBuilCChanged(_lineBuilC);
}

void ProfileManager::unsetLineBuilC()
{
    _lineBuilC.clear();
    lineBuilCChanged(_lineBuilC);
}

QString ProfileManager::lineApC() const
{
    return _lineApC;
}

void ProfileManager::resetAll()
{
    const QMetaObject* meta = metaObject();
    for(int i = 0; i < meta->propertyCount(); ++i)
    {
        if(meta->property(i).isResettable())
            meta->property(i).reset(this);
    }
}

void ProfileManager::setLineApC(const QString &lineApC)
{
    _lineApC = lineApC;
    lineApCChanged(_lineApC);
}

void ProfileManager::unsetLineApC()
{
    _lineApC.clear();
    lineApCChanged(_lineApC);
}

