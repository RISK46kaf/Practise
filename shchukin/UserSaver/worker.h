#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <botan/botan.h>
#include <botan/passhash9.h>
#include <string>
#include <vector>
#include <cstring>
#include <memory>
#include <streambuf>
#include <sstream>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);

signals:
    void workDone();
    void error(QString mess);
public slots:
    void startOperation(const QString& l, const QString& p, const QString& o);
    void Encrypt(Botan::SymmetricKey& key,
                 Botan::InitializationVector& iv,
                 const std::string& file2encrypt);
    void Decrypt(Botan::SymmetricKey& key,
                 Botan::InitializationVector& iv,
                 const std::string& file2encrypt);
};

#endif // WORKER_H
