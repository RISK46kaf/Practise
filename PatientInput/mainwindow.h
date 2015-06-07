#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyleFactory>
#include <QResizeEvent>
#include <QTimer>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
