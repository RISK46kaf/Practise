#ifndef FINDER_H
#define FINDER_H

#include <QMainWindow>
#include <QStyleFactory>
#include <QResizeEvent>
#include <QTimer>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileDialog>
#include <QGraphicsScene>

namespace Ui {
class Finder;
}

class Finder : public QMainWindow
{
    Q_OBJECT

public:
    explicit Finder(QWidget *parent = 0);
    ~Finder();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Finder *ui;
    QSqlDatabase db;
};

#endif // FINDER_H
