#ifndef ANALISIS_H
#define ANALISIS_H

#include <QObject>
#include <QListWidgetItem>

class Marker;

namespace Core {
class AnamnesManager;
class ProfileManager;
class DataBaseManager;
class RecognizeMediator;
struct MorphData;
struct MorphDataReal;

class Analisator : public QObject
{
    Q_OBJECT
public:
    explicit Analisator(QObject *parent = 0);

signals:

public slots:
    void startOperation(const QString& path,
                        DataBaseManager* dbm,
                        QVector<QPair<QListWidgetItem*,Marker*> >* markers, QString &answer);
private:
    void pirsonCorrelation(Core::DataBaseManager *dbm,
                           QVector<MorphData*>* currentData,
                           QMap<qint64, QVector<MorphData *>* > *morphMap,
                           QString& answer
                           );
    QVector<MorphDataReal *> meanByN(QVector<MorphData *> *data, qint64 N);
    QVector<MorphDataReal *> morh2real(QVector<MorphData *> *data);

    MorphDataReal pirsonIteration(QVector<MorphDataReal *> *first, QVector<MorphDataReal *> *second);
//    template <>
//    qreal pirsonIteration<qint64>(qint64 firstData, qint64 secondData);
//    template <>
//    qreal pirsonIteration<qreal>(qreal firstData, qreal secondData);

private:
    RecognizeMediator *mediator;
};

}
#endif // ANALISIS_H
