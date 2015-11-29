#include "profilemanager.h"

using namespace Core;

ProfileManager::ProfileManager(QObject *parent) : QObject(parent)
{

}

QString ProfileManager::lineMedCardID() const
{
    return _lineMedCardID;
}

void ProfileManager::setLineMedCardID(const QString &id)
{
    _lineMedCardID = id;
}

QString ProfileManager::linePSRN() const
{
    return _linePSRN;
}

void ProfileManager::setLinePSRN(const QString &psrn)
{
    _linePSRN = psrn;
}

QString ProfileManager::lineMedComID() const
{
    return _lineMedComID;
}

void ProfileManager::setLineMedComID(const QString &id)
{
    _lineMedComID = id;
}

QString ProfileManager::lineMedValID() const
{
    return _lineMedValID;
}

void ProfileManager::setLineMedValID(const QString &id)
{
    _lineMedValID = id;
}

QString ProfileManager::lineSnilsID() const
{
    return _lineSnilsID;
}

void ProfileManager::setLineSnilsID(const QString &id)
{
    _lineSnilsID = id;
}

QString ProfileManager::lineSale() const
{
    return _lineSale;
}

void ProfileManager::setLineSale(const QString &sale)
{
    _lineSale = sale;
}

QString ProfileManager::textSale() const
{
    return _textSale;
}

void ProfileManager::setTextSale(const QString &text)
{
    _textSale = text;
}

QString ProfileManager::lineName() const
{
    return _lineName;
}

void ProfileManager::setLineName(const QString &name)
{
    _lineName = name;
}

QString ProfileManager::dateBth() const
{
    return _dateBth;
}

void ProfileManager::setDateBth(const QString &data)
{
    _dateBth = data;
}

bool ProfileManager::sex() const
{
    return _sex;
}

void ProfileManager::setSex(bool sex)
{
    _sex = sex;
}

QString ProfileManager::lineRegR() const
{
    return _lineRegR;
}

void ProfileManager::setLineRegR(const QString &lineRegR)
{
    _lineRegR = lineRegR;
}

QString ProfileManager::lineDistrR() const
{
    return _lineDistrR;
}

void ProfileManager::setLineDistrR(const QString &lineDistrR)
{
    _lineDistrR = lineDistrR;
}

QString ProfileManager::lineLocR() const
{
    return _lineLocR;
}

void ProfileManager::setLineLocR(const QString &lineLocR)
{
    _lineLocR = lineLocR;
}

QString ProfileManager::lineStrR() const
{
    return _lineStrR;
}

void ProfileManager::setLineStrR(const QString &lineStrR)
{
    _lineStrR = lineStrR;
}

QString ProfileManager::lineHomR() const
{
    return _lineHomR;
}

void ProfileManager::setLineHomR(const QString &lineHomR)
{
    _lineHomR = lineHomR;
}

QString ProfileManager::lineBuilR() const
{
    return _lineBuilR;
}

void ProfileManager::setLineBuilR(const QString &lineBuilR)
{
    _lineBuilR = lineBuilR;
}

QString ProfileManager::lineApR() const
{
    return _lineApR;
}

void ProfileManager::setLineApR(const QString &lineApR)
{
    _lineApR = lineApR;
}

QString ProfileManager::lineRegC() const
{
    return _lineRegC;
}

void ProfileManager::setLineRegC(const QString &lineRegC)
{
    _lineRegC = lineRegC;
}

QString ProfileManager::lineDistrC() const
{
    return _lineDistrC;
}

void ProfileManager::setLineDistrC(const QString &lineDistrC)
{
    _lineDistrC = lineDistrC;
}

QString ProfileManager::lineLocC() const
{
    return _lineLocC;
}

void ProfileManager::setLineLocC(const QString &lineLocC)
{
    _lineLocC = lineLocC;
}

QString ProfileManager::lineStrC() const
{
    return _lineStrC;
}

void ProfileManager::setLineStrC(const QString &lineStrC)
{
    _lineStrC = lineStrC;
}

QString ProfileManager::lineHomC() const
{
    return _lineHomC;
}

void ProfileManager::setLineHomC(const QString &lineHomC)
{
    _lineHomC = lineHomC;
}

QString ProfileManager::lineBuilC() const
{
    return _lineBuilC;
}

void ProfileManager::setLineBuilC(const QString &lineBuilC)
{
    _lineBuilC = lineBuilC;
}

QString ProfileManager::lineApC() const
{
    return _lineApC;
}

void ProfileManager::setLineApC(const QString &lineApC)
{
    _lineApC = lineApC;
}

