#include "mainpicdialog.h"
#include "ui_mainpicdialog.h"

//MainPicDialog::MainPicDialog(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::MainPicDialog)
//{
//    ui->setupUi(this);
//    model = new QStandardItemModel(0,0,this);
//}

MainPicDialog::MainPicDialog(QSqlDatabase &DB, int publicID, QWidget *parent) :
     db(DB), idpublic_info(publicID),QDialog(parent),
    ui(new Ui::MainPicDialog)
{
    col_count = 5;
    ui->setupUi(this);
    model = new QStandardItemModel(0,0,this);
}

MainPicDialog::~MainPicDialog()
{
    delete model;
    delete ui;
}
