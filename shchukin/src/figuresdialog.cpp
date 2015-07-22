#include "figuresdialog.h"
#include "ui_figuresdialog.h"

FiguresDialog::FiguresDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FiguresDialog)
{
    ui->setupUi(this);
}

FiguresDialog::~FiguresDialog()
{
    delete ui;
}

void FiguresDialog::setList(QList<Arrow> *listOfArrows, QList<Rect> *listOfRects,
                            QList<Ellipse> *listOfEllipses, QList<Polygon> *listOfPolygons)
{
    for(int i(0); i < listOfArrows->count(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        int itemNum = ui->listWidget->count();
        newItem->setFlags(newItem->flags() | (
                              Qt::ItemIsUserCheckable /*|
                              Qt::ItemIsEnabled |
                              Qt::ItemIsEditable*/));
        newItem->setText(listOfArrows->operator [](i).getStrData());
        QString stylish_label_;
        stylish_label_.append(QString("<a>%1</a>").arg(listOfArrows->operator [](i).getStrData()));
        newItem->setToolTip(stylish_label_);

        ui->listWidget->addItem(newItem);
        ui->listWidget->setItemSelected(newItem, true);
        ui->listWidget->setCurrentItem(ui->listWidget->item(itemNum));
    }
    for(int i(0); i < listOfRects->count(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        int itemNum = ui->listWidget->count();
        newItem->setFlags(newItem->flags() | (
                              Qt::ItemIsUserCheckable /*|
                              Qt::ItemIsEnabled |
                              Qt::ItemIsEditable*/));
        newItem->setText(listOfRects->operator [](i).getStrData());
        QString stylish_label_;
        stylish_label_.append(QString("<a>%1</a>").arg(listOfRects->operator [](i).getStrData()));
        newItem->setToolTip(stylish_label_);

        ui->listWidget->addItem(newItem);
        ui->listWidget->setItemSelected(newItem, true);
        ui->listWidget->setCurrentItem(ui->listWidget->item(itemNum));
    }
    for(int i(0); i < listOfEllipses->count(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        int itemNum = ui->listWidget->count();
        newItem->setFlags(newItem->flags() | (
                              Qt::ItemIsUserCheckable /*|
                              Qt::ItemIsEnabled |
                              Qt::ItemIsEditable*/));
        newItem->setText(listOfEllipses->operator [](i).getStrData());
        QString stylish_label_;
        stylish_label_.append(QString("<a>%1</a>").arg(listOfEllipses->operator [](i).getStrData()));
        newItem->setToolTip(stylish_label_);

        ui->listWidget->addItem(newItem);
        ui->listWidget->setItemSelected(newItem, true);
        ui->listWidget->setCurrentItem(ui->listWidget->item(itemNum));
    }
    for(int i(0); i < listOfPolygons->count(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        int itemNum = ui->listWidget->count();
        newItem->setFlags(newItem->flags() | (
                              Qt::ItemIsUserCheckable /*|
                              Qt::ItemIsEnabled |
                              Qt::ItemIsEditable*/));
        newItem->setText(listOfPolygons->operator [](i).getStrData());
        QString stylish_label_;
        stylish_label_.append(QString("<a>%1</a>").arg(listOfPolygons->operator [](i).getStrData()));
        newItem->setToolTip(stylish_label_);

        ui->listWidget->addItem(newItem);
        ui->listWidget->setItemSelected(newItem, true);
        ui->listWidget->setCurrentItem(ui->listWidget->item(itemNum));
    }
}
