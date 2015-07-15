#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
    view_label = new QLabel();
    ui->scrollArea->setWidget(view_label);
}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::on_actionOpen_triggered()
{
    fileNames = QFileDialog::getOpenFileNames(this,tr("Open"),tr("C:\\Users\\ivanov\\Pictures"),tr("Files(*.png *.jpg *.bmp)"));
    QPixmap img;
    img.load(fileNames[0]);
    view_label->setPixmap(img);
    ui->listWidget->setFlow(QListWidget::LeftToRight);
    ui->listWidget->setIconSize(QSize(100,100));
    for(uint i=0;i<fileNames.size();++i)
    {
        img.load(fileNames[i]);
        QPixmap pm = img.scaled(QSize(100,100),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        pm.save("C:\\Users\\ivanov\\icon.png","PNG");
        QListWidgetItem* item = new QListWidgetItem();
        //icon.addPixmap(pm);
        item->setText(fileNames[i]);
        item->setIcon(QIcon(pm));
        item->setSizeHint(QSize(100,100));
        items.push_back(item);
        ui->listWidget->addItem(item);
    }
}


void Viewer::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QPixmap img;
    img.load(item->text());
    //дальшеэто изображение выводить на экран
}
