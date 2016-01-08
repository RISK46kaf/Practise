#include "worker.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

Worker::Worker(QObject *parent) : QObject(parent)
{
}

void Worker::startOperation(const QString &l, const QString &p, const QString &o)
{
    std::string fileName = (o + "/.forefather").toStdString();
    Botan::LibraryInitializer init;
    std::string passPhrase = "HpcbYTB4~dymbD%eUm3wbkauw2B?F1IsGZqOJN}$JmsB2ezH?UFC54qPWAw3ve8r";
    std::string salt = "aDpF06WwmVZ?8s7BVbBAfr@P9Ql8WeSrmJkgKh8{aL}plNIl0lT$RMoEVGXaFyFv";
    Botan::AutoSeeded_RNG rng;
    Botan::S2K* s2k = Botan::get_s2k("PBKDF2(SHA-512)");

    Botan::SecureVector<Botan::byte> key_and_IV =
            s2k->derive_key(48,passPhrase,(const Botan::byte*)salt.c_str(),salt.size(),8098)
            .bits_of();
    Botan::SymmetricKey key(key_and_IV, 32);
    Botan::InitializationVector iv(key_and_IV + 32, 16);
    Decrypt(key,iv,fileName);
    Botan::AutoSeeded_RNG pRng;
    std::string phrase = (l + p).toStdString();
    std::string hash = Botan::generate_passhash9(phrase,pRng,100,1);
    std::ofstream out(fileName, std::ios::binary | std::ofstream::app);
    out << hash << "\n";
    out.flush();
    out.close();
    Encrypt(key,iv,fileName);
    emit workDone();
}

void Worker::Encrypt(Botan::SymmetricKey &key,
                     Botan::InitializationVector &iv,
                     const std::__1::string &file2encrypt)

{
    QFileInfo fi(QString::fromStdString(file2encrypt));
    if(!fi.exists())
        return;
    QFile file(QString::fromStdString(file2encrypt));
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray filedata = file.readAll();
        file.close();
        std::string str(filedata.data(),filedata.length());
        std::istringstream stream_in(str);
        std::stringstream stream_out;
        Botan::Pipe pipe(Botan::get_cipher("AES-256/OFB",key,iv,Botan::ENCRYPTION),
                         new Botan::DataSink_Stream(stream_out));
        pipe.start_msg();
        stream_in >> pipe;
        pipe.end_msg();
        stream_out.flush();
        std::string outta = stream_out.str();
        if(file.open(QIODevice::WriteOnly))
        {
            file.write(QByteArray(outta.c_str(), outta.length()));
            file.close();
        }
        else
            qDebug() << "cannot write only open" << QString::fromStdString(file2encrypt);
    }
    else
        qDebug() << "cannot read only open" << QString::fromStdString(file2encrypt);
}

void Worker::Decrypt(Botan::SymmetricKey &key, Botan::InitializationVector &iv, const std::__1::string &file2encrypt)
{
    QFileInfo fi(QString::fromStdString(file2encrypt));
    if(!fi.exists())
        return;
    QFile file(QString::fromStdString(file2encrypt));
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray filedata = file.readAll();
        file.close();
        std::string str(filedata.data(),filedata.length());
        std::istringstream stream_in(str);
        std::stringstream stream_out;
        Botan::Pipe pipe(Botan::get_cipher("AES-256/OFB",key,iv,Botan::DECRYPTION),
                         new Botan::DataSink_Stream(stream_out));
        pipe.start_msg();
        stream_in >> pipe;
        pipe.end_msg();
        stream_out.flush();
        std::string outta = stream_out.str();
        if(file.open(QIODevice::WriteOnly))
        {
            file.write(QByteArray(outta.c_str(), outta.length()));
            file.close();
        }
        else
            qDebug() << "cannot write only open" << QString::fromStdString(file2encrypt);
    }
    else
        qDebug() << "cannot read only open" << QString::fromStdString(file2encrypt);
}
