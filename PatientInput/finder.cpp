<<<<<<< HEAD
#include "finder.h"
#include "ui_finder.h"

Finder::Finder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Finder)
{
    ui->setupUi(this);
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }QPushButton:disabled{color: #353030; }QPushButton::checked{color: #2A82DA; }");


    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("mydb"); //название бд
    db.setUserName("root");
    db.setPassword("12345");
    if (db.open())
        qDebug() << "OK!";
    else
        qDebug() << "error db!";
}

Finder::~Finder()
{
    delete ui;
}

void Finder::on_pushButton_clicked()
{
    QSqlQuery q;
    QString name = ui->nameEdit->text()+" "+ui->name2Edit->text()+" "+ui->name3Edit->text();
    q.prepare("SELECT * FROM patient WHERE fullname=':name'");
    q.bindValue(":name",name);
    q.exec();
    q.next();
    qDebug()<<q.value(0).toString();
    qDebug()<<q.value(1).toString();

}
=======
#include "finder.h"
#include "ui_finder.h"

Finder::Finder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Finder)
{
    ui->setupUi(this);
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }QPushButton:disabled{color: #353030; }QPushButton::checked{color: #2A82DA; }");


    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("mydb"); //название бд
    db.setUserName("root");
    db.setPassword("12345");
    if (db.open())
        qDebug() << "OK!";
    else
        qDebug() << "error db!";
}

Finder::~Finder()
{
    delete ui;
}

void Finder::on_pushButton_clicked()
{
    QSqlQuery q;
    QString name = ui->nameEdit->text()+" "+ui->name2Edit->text()+" "+ui->name3Edit->text();
    q.prepare("SELECT * FROM patient WHERE fullname=':name'");
    q.bindValue(":name",name);
    q.exec();
    q.next();
    qDebug()<<q.value(0).toString();
    qDebug()<<q.value(1).toString();

}
>>>>>>> 658142fd0309869fc410363f6e774d62bcdbf656
