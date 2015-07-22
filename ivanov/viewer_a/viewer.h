#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsView>
#include <iostream>
#include <QListWidget>
#include <QLabel>
#include <QPixmap>
#include <QStyleFactory>


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

    void on_actionHide_ShowRight_triggered();

    void on_actionHide_ShowBottom_triggered();

private:
    Ui::Viewer *ui;
    QStringList fileNames;
    vector<QListWidgetItem*> items;
    QLabel* view_label;
    int defaultToolsWidth;
    int defaultPreviewHeight;
};

#endif // VIEWER_H
