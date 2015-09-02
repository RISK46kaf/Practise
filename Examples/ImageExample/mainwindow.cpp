#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    v = new View();
    ui->gridLayout->addWidget(v);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete v;
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), "C:/Users/<USER>/Pictures" , tr("Image Files (*.png *.jpg *.bmp *.gif)"));
    if(!path.isEmpty())
    {
        QImage img(path);
        v->setImage(img);
    }
}
