#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>
#include <QStyleFactory>
#include <QDir>
#include <QPainter>
#include <QCryptographicHash>


namespace Ui {
class Welcome;
}

class Welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = 0);

    ~Welcome();

protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Welcome *ui;
    bool auth_b;
signals:
    void auth();

};

#endif // WELCOME_H
