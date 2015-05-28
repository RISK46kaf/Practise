#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "storage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->horizontalLayout);
    ui->frame->setLayout(ui->gridLayout);
    storage_ = new Storage;
    storage_->setBackgroundRole(QPalette::Background);
    storage_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    storage_->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->scrollArea->setWidget(storage_);
    ui->frame_2->setLayout(ui->verticalLayout);
    storage_size_ = ui->scrollArea->size();
    storage_->resize(storage_size_);
}

MainWindow::~MainWindow()
{
    delete ui;
}
