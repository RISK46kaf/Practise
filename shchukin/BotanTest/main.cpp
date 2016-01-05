#include <QCoreApplication>
#include <botan/botan.h>

#include <QDebug>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <memory>

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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug("Starting Botan");

    std::string plainText = "/Users/Yarique/Documents/BotanTest/plaintext.zip";
    std::string encrypted = "/Users/Yarique/Documents/BotanTest/encrypted.dat";
    std::string decrypted = "/Users/Yarique/Documents/BotanTest/decrypted.zip";

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

    Encrypt(key,iv,plainText,encrypted);
    Decrypt(key,iv,encrypted,decrypted);

    return a.exec();
}
