#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

namespace Ui {
class Welcome;
}

namespace Core {
class DataBaseManager;
}

class Input;
class Output;

class Welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = 0);
    ~Welcome();
protected:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

private slots:
    void on_pushButton_clicked();
    void onOpenMode(int);

private:
    Ui::Welcome *ui;
    Core::DataBaseManager* _dbManager;
    Input* _input;
    Output* _output;
};

#endif // WELCOME_H
