#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QStandardPaths>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_Image_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QVector<QGraphicsPixmapItem*> items;
};

#endif // MAINWINDOW_H
