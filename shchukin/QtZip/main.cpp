#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include "zipreader.h"
#include "zipwriter.h"

void compess(const QString& sourceName, const QString zipFileName = "")
{
    if(sourceName.isEmpty())
    {
        qDebug("source is empty");
        return;
    }
    QFileInfo sourceInfo(sourceName);
    if(sourceInfo.isDir())
    {
        QDir dir(sourceName);
        QString zippy = !zipFileName.isEmpty() ?
                    zipFileName
                  : sourceName.endsWith("/")
                        ?
                            QString(sourceName)
                            .remove(sourceName.size() - 1, 1) + ".zip"
                        : sourceName + ".zip";
        QFileInfoList allFiles = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
        ZipWriter cZip(zippy);
        cZip.setCreationPermissions(QFile::WriteOther | QFile::ReadOther);
        cZip.setCompressionPolicy(ZipWriter::AlwaysCompress);
        foreach (QFileInfo item, allFiles) {
            QString abs = item.absoluteFilePath();
            QString dirN = item.dir().dirName();
            QFile file(abs);
            file.open(QIODevice::ReadOnly);
            cZip.addFile(dirN + "/" + dir.relativeFilePath(abs), file.readAll());
            file.close();
        }
        cZip.close();
    }
    else if(sourceInfo.isFile())
    {
        QString zippy = !zipFileName.isEmpty() ?
                    zipFileName
                        : sourceInfo.dir().absolutePath() + "/"
                            + sourceInfo.baseName() + ".zip";
        ZipWriter cZip(zippy);
        cZip.setCreationPermissions(QFile::WriteOther | QFile::ReadOther);
        cZip.setCompressionPolicy(ZipWriter::AlwaysCompress);
        QString abs = sourceInfo.absoluteFilePath();
        QFile file(abs);
        file.open(QIODevice::ReadOnly);
        cZip.addFile(sourceInfo.fileName(), file.readAll());
        file.close();
    }
    else
    {
        qDebug("nothing compress");
    }
}

void decompess(const QString& zipFileName, const QString& extractDirName = "")
{
    ZipReader cZip(zipFileName);
    QString dirName = extractDirName.isEmpty() ?
                        QString(zipFileName)
                            .replace(".zip","") + "/" :
                                extractDirName;

    QDir dir(dirName);
    if(!dir.exists())
        dir.mkpath(".");
    foreach (ZipReader::FileInfo item, cZip.fileInfoList()) {
//        qDebug() << item.filePath;
        QString fileName = QFileInfo(dirName).absoluteFilePath() + item.filePath;
        QDir tmpDir = QFileInfo(fileName).dir();
        if(!tmpDir.exists())
            tmpDir.mkpath(".");
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        file.write(cZip.fileData(item.filePath));
        file.close();
    }
    cZip.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString sourceDir = "../QtZip/Images/_2.jpg";
    compess(sourceDir);
    decompess("../QtZip/Images/_2.zip");//sourceDir + ".zip");

    return 0;//a.exec();
}
