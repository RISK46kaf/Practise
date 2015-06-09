#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QScrollBar>

class Storage;

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
    void on_openButton_clicked();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

    void on_zoomAutoButton_clicked();

private:
    Storage *storage_;
    QSize storage_size_;
    void openImage();
    void autoZoom();
    void zoomChange(bool in);
    QPixmap _image;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
