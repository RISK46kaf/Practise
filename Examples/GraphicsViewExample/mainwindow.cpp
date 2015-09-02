#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    ui->verticalLayout->addWidget(view);
}


MainWindow::~MainWindow()
{
    delete scene;
    delete view;
    delete ui;
    for(uint i=0;i<items.size();++i)
        delete items[i];
}

void MainWindow::on_actionLoad_Image_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), "C:/Users/<USER>/Pictures" , tr("Image Files (*.png *.jpg *.bmp)"));
    for(uint i=0;i<10;++i)
    {
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(path);
        if(items.size()>0)
        {
            item->setPos(QPoint(items.last()->pos().x()+items.last()->pixmap().size().width(),0));
        }
        items.push_back(item);
        scene->addItem(item);
    }
}
