#ifndef SENDER_H
#define SENDER_H

#include <QObject>


class QListWidgetItem;
class Marker;

namespace Core {

class AnamnesManager;
class ProfileManager;
class DataBaseManager;
class RecognizeMediator;

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = 0);

signals:

public slots:
    void startOperation(const QString& path, const QString &about,
                        DataBaseManager* dbm,
                        AnamnesManager* am,
                        ProfileManager* pm,
                        QVector<QPair<QListWidgetItem*,Marker*> >* markers);

private:
    Core::RecognizeMediator *mediator;
//    qint64 anamnesId;
//    qint64 profileId;
//    Core::DataBaseManager* dbM;
};

}
#endif // SENDER_H
