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
    //ui->treeWidget->header() ->close ();
    storage_->resize(storage_size_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage()
{
    QFileDialog fd(0,tr("Open Image"),QString("%1/Pictures").arg(QDir::homePath()),QString("Images (*.png *.jpeg *.jpg *.bmp *.pbm *.pgm *.ppm *.xbm *.xpm)"));
    fd.setFileMode(QFileDialog::ExistingFile);
    if(fd.exec())
    {
        QString filename(fd.selectedFiles().last());
        if(!_image.load(filename)) return;
        ui->zoomInButton->setEnabled(true);
        ui->zoomOutButton->setEnabled(true);
        ui->zoomAutoButton->setEnabled(true);
        autoZoom();
    }
}

void MainWindow::autoZoom()
{
    if(_image.isNull()) return;
    storage_->resize(storage_size_);
    QSize imageSize = _image.size();
    double s = 1;
    while(storage_size_.width() * s < imageSize.width() - 200 ||
          storage_size_.height() * s < imageSize.height() - 200)
    {
        s *= 1.0005;
    }
    storage_->resize(imageSize);
    storage_->setPixmap(_image);
    storage_->scaleStorage(ZoomOut,s);
}

void MainWindow::zoomChange(bool plus)
{
    if(_image.isNull()) return;
    double s = 1.25;
    storage_->setPixmap(_image);
    if(plus) storage_->scaleStorage(ZoomIn,s);
    else storage_->scaleStorage(ZoomOut,s);
    ui->scrollArea->horizontalScrollBar()->setValue((ui->scrollArea->horizontalScrollBar()->maximum()+ui->scrollArea->horizontalScrollBar()->minimum())/2);
    ui->scrollArea->verticalScrollBar()->setValue((ui->scrollArea->horizontalScrollBar()->maximum()+ui->scrollArea->horizontalScrollBar()->minimum())/2);
}
void MainWindow::on_openButton_clicked()
{
    openImage();
}

void MainWindow::on_zoomInButton_clicked()
{
    zoomChange(true);
}

void MainWindow::on_zoomOutButton_clicked()
{
    zoomChange(false);
}

void MainWindow::on_zoomAutoButton_clicked()
{
    storage_size_=QSize(805,605);
    autoZoom();
}
