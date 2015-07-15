#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsView>
#include <iostream>
#include <QListWidget>
#include <QLabel>
#include <QPixmap>


using namespace std;


namespace Ui {
class Viewer;
}

class Viewer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();
    
private slots:
    void on_actionOpen_triggered();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Viewer *ui;
    QStringList fileNames;
    vector<QListWidgetItem*> items;
    QLabel* view_label;
};

#endif // VIEWER_H
