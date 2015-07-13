#include "welcome.h"
#include "ui_welcome.h"
#include <QDebug>
#include <QTime>
#include <QtGlobal>

Welcome::Welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Welcome)
{
    auth_b = false;
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
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->verticalLayout);
    ui->comboBox->lineEdit()->setReadOnly(true);
    ui->comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox->addItem(QString("Insert Mode"));
    ui->comboBox->addItem(QString("Search Mode"));
//    setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
    setWindowFlags(Qt::Tool
    | Qt::WindowTitleHint
    | Qt::WindowMinimizeButtonHint
    | Qt::WindowCloseButtonHint
    | Qt::CustomizeWindowHint);

}

Welcome::~Welcome()
{
    delete ui;
}

void Welcome::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter p(this);
    QPixmap tmp(":/MyFiles/logo.jpg");
    p.drawPixmap((this->width()-tmp.width())/2,(ui->frame->height()-tmp.height())/2,tmp);
}

void Welcome::on_pushButton_clicked()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QByteArray salt = QByteArray(QString::number(qrand()).toUtf8());
    QByteArray salt_local = QString("My local salt").toUtf8();

    QByteArray def_pass = QCryptographicHash::hash(QString("12345").toUtf8()+salt+salt_local, QCryptographicHash::Sha3_256); //12345 - пароль

    //проверка введенного пароля
    QByteArray input_data = ui->lineEdit_3->text().toUtf8();
    QByteArray hash = QCryptographicHash::hash(input_data+salt+salt_local, QCryptographicHash::Sha3_256);
    if((hash == def_pass) && ui->comboBox->currentIndex() == 0)
    {
        emit auth_i();
        this->hide();
    }
    if((hash == def_pass) && ui->comboBox->currentIndex() == 1)
    {
        emit auth_f();
        this->hide();
    }

}

