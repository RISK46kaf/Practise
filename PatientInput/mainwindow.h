#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "markingtools.h"

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *);
private slots:
    void on_comboBoxM_currentIndexChanged(const QString &arg1);

    void on_spinBoxYr_valueChanged(int arg1);

    void correctData();

    void on_actionAdd_triggered();

    void on_loadButton_clicked();

    void on_pushButtonAEP_clicked();

    void on_saveButton_clicked();

    void on_addMarkButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QString foto_path;
    QGraphicsScene* scene;
    QStringList images_path;
};

#endif // MAINWINDOW_H
