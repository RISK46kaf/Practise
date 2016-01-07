#ifndef USERSAVER_H
#define USERSAVER_H

#include <QMainWindow>

class Worker;

namespace Ui {
class UserSaver;
}

class UserSaver : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserSaver(QWidget *parent = 0);
    ~UserSaver();

protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::UserSaver *ui;
    QThread* _workThread;
    Worker* _worker;
    QString _lastCorrectO;
signals:
    void startOperation(const QString& l, const QString& p, const QString& o);
};

#endif // USERSAVER_H
