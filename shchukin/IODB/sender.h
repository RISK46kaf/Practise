#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QListWidgetItem>
#include "morphdata.h"

namespace Core {
class AnamnesManager;
class ProfileManager;
class DataBaseManager;
}

class Marker;
class RecognizeMediator;

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = 0);

signals:

public slots:
    void startOperation(const QString& path,
                        Core::DataBaseManager* dbm,
                        Core::AnamnesManager* am,
                        Core::ProfileManager* pm,
                        QVector<QPair<QListWidgetItem*,Marker*> >* markers);

private:
    RecognizeMediator *mediator;
    qint64 anamnesId;
    qint64 profileId;
    Core::DataBaseManager* dbM;
};

#endif // SENDER_H
