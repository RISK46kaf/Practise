#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QHash>

class QTimer;
class Marker;

namespace Core {

class AnamnesManager;
class ProfileManager;
struct MorphData;

enum Mode{
    PermissionDenied = -1,
    Write = 0,
    Read = 1
};

class DataBaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseManager(QObject *parent = 0, const char* driverName = "QMYSQL",
            int port = 3306, const QString& schemaName = "Exp_sys", uint checkTimeDiaposonMs = 300000);
    ~DataBaseManager();
    bool connect(const QString& user, const QString& host,
                 const QString& pass, int mode);
    qint64 writeProfile(ProfileManager* profileManager, qint64 anamnesId);
    qint64 writeAnamnes(AnamnesManager* anamnesManager);
    qint64 writeMarker(Marker* marker, const QString &imgPath, const QString &about, qint64 profileId);
    qint64 writeMorphology(MorphData& data, qint64 markerId);
    QString readDiagnosisById(qint64 id, bool *ok = 0);
    void readPreview(QList<QPair<qint64, QString> >* previewList);
    bool readProfileAndAnamnes(ProfileManager* profileManager, AnamnesManager* anamnesManager, qint64 profileId);
    bool readAnamnes(AnamnesManager* anamnesManager, qint64 profileId);
    bool readMorphology(QMap<qint64, QVector<MorphData *> *> *morphMap);
signals:
    void openMode(int);
    void updatePreviewListWidget();
private slots:
    void checkPreview();
private:
    Mode _mode;
    QSqlDatabase _db;
    QString _user;
    QString _host;
    QString _pass;
//    QMap<qint64, QPair<ProfileManager*,AnamnesManager*> > _profiles;
    const int _port;
    const QString _schema_name;
    uint _previewHash;
    QTimer* _previewCheckTimer;
    QList<QPair<qint64, QString> >* _previewList;
    uint _checkTimeDiaposonMs;

};

}
#endif // DATABASEMANAGER_H
