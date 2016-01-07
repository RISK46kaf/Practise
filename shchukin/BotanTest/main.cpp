#include <QCoreApplication>
#include <botan/botan.h>
#include <botan/passhash9.h>

#include <QDebug>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <memory>
#include <streambuf>
#include <sstream>
#include <QBuffer>
#include <QFile>
#include <QDir>
#include <QThread>
#include <QtCore>


///The encoder

void Encrypt(Botan::SymmetricKey& key,
             Botan::InitializationVector& iv,
             const std::string& inFile,
             const std::string& outFile)
{
    std::ifstream in(inFile.c_str(),std::ios::binary);
    std::ofstream out(outFile.c_str(),std::ios::binary);

    Botan::Pipe pipe(Botan::get_cipher("AES-256/OFB",key,iv,Botan::ENCRYPTION),
                     new Botan::DataSink_Stream(out));
    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();
    out.flush();
    out.close();
    in.close();
    qDebug("Encrypted!");
}

struct membuf : std::streambuf
{
    membuf(char* begin, char* end) {
        this->setg(begin, begin, end);
    }
};

void EncryptByteArray(Botan::SymmetricKey& key,
                      Botan::InitializationVector& iv,
                      QByteArray& inArray,
                      QByteArray& outArray)
{
    QString dirName1 = QDir::tempPath() + "/BotanTest/PlainText/";
    QString dirName2 = QDir::tempPath() + "/BotanTest/Encrypted/";
    QDir dir(dirName1);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }
    dir = QDir(dirName2);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }
    QString plainText =
            dirName1 + QString::number((qint64)QThread::currentThreadId(),16) + ".txt";
    QString encrypted =
            dirName2 + QString::number((qint64)QThread::currentThreadId(),16) + ".txt";
    QFile file1(plainText);
    file1.open(QIODevice::WriteOnly);
    file1.write(inArray);
    file1.close();
    Encrypt(key,iv,plainText.toStdString(),encrypted.toStdString());
    QFile file2(encrypted);
    file2.open(QIODevice::ReadOnly);
    outArray = file2.readAll();
    file2.close();
    QDir tmpDir(QFileInfo(QDir::tempPath()
                       + "/BotanTest/").absolutePath());
    tmpDir.setNameFilters(QStringList() << "*.*");
    tmpDir.setFilter(QDir::Files);
    foreach(QString dirFile, tmpDir.entryList())
    {
        tmpDir.remove(dirFile);
    }
    if (!tmpDir.exists()) {
        tmpDir.mkpath(".");
    }
}

void Decrypt(Botan::SymmetricKey& key,
             Botan::InitializationVector& iv,
             const std::string& inFile,
             const std::string& outFile)
{
    std::ifstream in(inFile.c_str(),std::ios::binary);
    std::ofstream out(outFile.c_str(),std::ios::binary);

    Botan::Pipe pipe(Botan::get_cipher("AES-256/OFB",key,iv,Botan::DECRYPTION),
                     new Botan::DataSink_Stream(out));
    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();
    out.flush();
    out.close();
    in.close();
    qDebug("Decrypted!");
}

void DecryptByteArray(Botan::SymmetricKey& key,
                      Botan::InitializationVector& iv,
                      QByteArray& inArray,
                      QByteArray& outArray)
{
    QString dirName1 = QDir::tempPath() + "/BotanTest/Encrypted/";
    QString dirName2 = QDir::tempPath() + "/BotanTest/Decrypted/";
    QDir dir(dirName1);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }
    dir = QDir(dirName2);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }
    QString plainText =
            dirName1 + QString::number((qint64)QThread::currentThreadId(),16) + ".txt";
    QString encrypted =
            dirName2 + QString::number((qint64)QThread::currentThreadId(),16) + ".txt";
    QFile file1(plainText);
    file1.open(QIODevice::WriteOnly);
    file1.write(inArray);
    file1.close();
    Decrypt(key,iv,plainText.toStdString(),encrypted.toStdString());
    QFile file2(encrypted);
    file2.open(QIODevice::ReadOnly);
    outArray = file2.readAll();
    file2.close();
    QDir tmpDir(QFileInfo(QDir::tempPath()
                       + "/BotanTest/").absolutePath());
    tmpDir.setNameFilters(QStringList() << "*.*");
    tmpDir.setFilter(QDir::Files);
    foreach(QString dirFile, tmpDir.entryList())
    {
        tmpDir.remove(dirFile);
    }
    if (!tmpDir.exists()) {
        tmpDir.mkpath(".");
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug("Starting Botan");

    std::string plainText = "../BotanTest/plaintext.zip";
    std::string encrypted = "../BotanTest/encrypted.dat";
    std::string decrypted = "../BotanTest/decrypted.zip";

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

    QByteArray inA = "победа!";
    QByteArray c;
    QByteArray p;
    EncryptByteArray(key,iv,inA,c);
    qDebug() << QString(inA) << QString(c);
    DecryptByteArray(key,iv,c,p);

    qDebug() << QString(c) << QString(p);

    //    Encrypt(key,iv,plainText,encrypted);
    //    Decrypt(key,iv,encrypted,decrypted);

//    qDebug() << "passhash9 write";
//    Botan::AutoSeeded_RNG pRng;
//    std::string password = "pass";
//    std::string hash = Botan::generate_passhash9(password,pRng,100,1);

//    qDebug() << QString(password.c_str()) << " and their hash " <<
//                QString(hash.c_str());

//    //    std::cin >> hash;
//    std::ofstream out("../BotanTest/hash.txt",std::ios::binary | std::ofstream::app);
//    out << hash << "\n";
//    out.flush();
//    out.close();

//    qDebug() << "passhash9 write ends";
//    qDebug("check");
//    std::ifstream in("../BotanTest/hash.txt",std::ios::binary);
//    for( std::string line; std::getline( in, line ); )
//    {
//        qDebug() << Botan::check_passhash9(password, line);
//    }
//    qDebug("checked");

    return a.exec();
}
