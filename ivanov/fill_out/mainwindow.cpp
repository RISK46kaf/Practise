#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("mydb"); //название бд
    db.setUserName("root");
    db.setPassword("12345");

    if(db.open())
    {
        for(char i=0;i<2;++i)
            ui->tableWidget->insertColumn(i);
        QSqlQuery q;
        q.exec("select * from table1"); //table1 - название таблицы
        //q.first();
        while(q.next())
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            for(char i=0;i<2;++i)
            {
                QTableWidgetItem *item = new QTableWidgetItem(q.value(i).toString());
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,i,item);
            }
        }
    }
    else
    {
        qDebug()<<"error";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDelete_all_triggered()
{
    QSqlQuery q;
    q.exec("delete from table1");
    if(db.open())
    {
        //QSqlQuery q;
        q.exec("select * from table1"); //table1 - название таблицы
        //q.first();
        while(q.next())
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            for(char i=0;i<2;++i)
            {
                QTableWidgetItem *item = new QTableWidgetItem(q.value(i).toString());
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,i,item);
            }
        }
    }
    else
    {
        qDebug()<<"error";
    }
}
