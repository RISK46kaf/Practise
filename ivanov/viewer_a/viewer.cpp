#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->verticalLayout);
    ui->frameTools->setLayout(ui->verticalLayoutInfo);
    defaultToolsWidth = ui->frameTools->maximumWidth();
    defaultPreviewHeight = ui->listWidget->maximumHeight();
    view_label = new QLabel();
//    ui->scrollAreaLeft->setWidget(view_label);
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
    ///что за трэш ???
//    QPixmap img;
//    img.load(item->text());
    ///
    //дальшеэто изображение выводить на экран
}

void Viewer::on_actionHide_ShowRight_triggered()
{
    QList< int > _sizes = ui->splitter_2->sizes() ;
    if(!_sizes.last())
    {
        ui->actionHide_ShowRight->setIcon(QIcon(":/icons/Right_arrow_fold_button_32.png"));
        _sizes.first() -= defaultToolsWidth;
        _sizes.last() += defaultToolsWidth;
        ui->splitter_2->setSizes(_sizes);
    }
    else
    {
        ui->actionHide_ShowRight->setIcon(QIcon(":/icons/Left_arrow_fold_button_32.png"));
        _sizes.first() += _sizes.last() ;
        _sizes.last() = 0;
        ui->splitter_2->setSizes(_sizes);
    }
}

void Viewer::on_actionHide_ShowBottom_triggered()
{
    QList< int > _sizes = ui->splitter_3->sizes() ;
    if(!_sizes.last())
    {
        ui->actionHide_ShowBottom->setIcon(QIcon(":/icons/Down_arrow_fold_button_32.png"));
        _sizes.first() -= defaultPreviewHeight;
        _sizes.last() += defaultPreviewHeight;
        ui->splitter_3->setSizes(_sizes);
    }
    else
    {
        ui->actionHide_ShowBottom->setIcon(QIcon(":/icons/Up_arrow_fold_button_32.png"));
        _sizes.first() += _sizes.last();
        _sizes.last() = 0;
        ui->splitter_3->setSizes(_sizes);
    }
}
