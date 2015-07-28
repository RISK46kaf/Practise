#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    ui->groupBoxP->setLayout(ui->gridLayoutP);
    ui->groupBoxPh->setLayout(ui->verticalLayoutP);
    ui->groupBoxDi->setLayout(ui->gridLayoutDi);
    ui->centralWidget->setLayout(ui->gridLayoutMain);
    ui->groupBoxPwE->setLayout(ui->verticalLayoutPwE);
    ui->groupBoxSU->setLayout(ui->verticalLayoutSU);
    ui->comboBoxM->addItem(QString("Jan"));
    ui->comboBoxM->addItem(QString("Feb"));
    ui->comboBoxM->addItem(QString("Mar"));
    ui->comboBoxM->addItem(QString("Apr"));
    ui->comboBoxM->addItem(QString("May"));
    ui->comboBoxM->addItem(QString("Jun"));
    ui->comboBoxM->addItem(QString("Jul"));
    ui->comboBoxM->addItem(QString("Aug"));
    ui->comboBoxM->addItem(QString("Sep"));
    ui->comboBoxM->addItem(QString("Oct"));
    ui->comboBoxM->addItem(QString("Nov"));
    ui->comboBoxM->addItem(QString("Dec"));
    ui->comboBoxS->addItem(QString("Mal"));
    ui->comboBoxS->addItem(QString("Fem"));
    ui->comboBoxM->setCurrentIndex(0);

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
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    //    qDebug() << size();
}

void MainWindow::on_comboBoxM_currentIndexChanged(const QString &arg1)
{
    qDebug() << arg1;
    correctData();
}

void MainWindow::on_spinBoxYr_valueChanged(int arg1)
{
    correctData();
    //    QTimer go;
    //    go.start(1500);
    //    connect(&go,SIGNAL(timeout()),this,SLOT(correctData()));
}

void MainWindow::correctData()
{
    switch (ui->comboBoxM->currentIndex()) {
    case 0:
        ui->spinBoxD->setMaximum(31);
        break;
    case 1:
    {
        if(ui->spinBoxYr->value()%4 == 0)
        {
            ui->spinBoxD->setMaximum(29);
            qDebug("29");
            if(!ui->spinBoxYr->value()%100 && ui->spinBoxYr->value()%400)
            {
                ui->spinBoxD->setMaximum(28);
                qDebug("28");
                qDebug("sd");
                return;
            }
            if(!ui->spinBoxYr->value()%100 && !ui->spinBoxYr->value()%400)
            {
                ui->spinBoxD->setMaximum(29);
                qDebug("29");
                return;
            }
            return;
        }
        ui->spinBoxD->setMaximum(28);
        qDebug("28");
        qDebug() << ui->spinBoxYr->value()%4;
    }
        break;
    case 2:
        ui->spinBoxD->setMaximum(31);
        break;
    case 3:
        ui->spinBoxD->setMaximum(30);
        break;
    case 4:
        ui->spinBoxD->setMaximum(31);
        break;
    case 5:
        ui->spinBoxD->setMaximum(30);
        break;
    case 6:
        ui->spinBoxD->setMaximum(31);
        break;
    case 7:
        ui->spinBoxD->setMaximum(31);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionAdd_triggered()
{
    QSqlQuery q;
    QString first_name = ui->lineEdit1n->text();
    QString last_name = ui->lineEdit2n->text();
    QString patronymic = ui->lineEdit3n->text();
    QString full_name = first_name+" "+last_name+" "+patronymic;
    bool sex;
    if(ui->comboBoxS->currentIndex() == 0)
        sex = 0;
    else
        sex = 1;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    uint unique_val=qrand()%10000;


    q.exec("select MAX(idpatient) from patient");
    q.next();
    int idpatient =0;
    if(q.value(0).toInt()>0)
        idpatient=q.value(0).toInt() + 1;

    QString health_insurance_id = ui->lineEditMI->text();
    QString phone_number = ui->lineEditPh->text();
    QString email = ui->lineEditEm->text();
    uint y = ui->spinBoxYr->value();
    uint m = ui->comboBoxM->currentIndex()+1;
    uint d = ui->comboBoxM->currentIndex()+1;
    QDate birth_date = QDate(y,m,d);
    QFile photo(foto_path);
    photo.open(QIODevice::ReadOnly);
    QByteArray bytes = photo.readAll();
    q.prepare("insert into patient(idpatient,fullname,birth_date,sex,health_insurance_id,phone_number,email,photo) values (:idpatient,:fullname,:birth_date,:sex,:health_insurance_id,:phone_number,:email,:photo)");
    q.bindValue(":idpatient",idpatient);
    q.bindValue(":fullname",full_name);
    q.bindValue(":birth_date",birth_date);
    q.bindValue(":sex",sex);
    q.bindValue(":health_insurance_id",health_insurance_id);
    //q.bindValue(":unique_val",unique_val);
    q.bindValue(":phone_number",phone_number);
    q.bindValue(":email",email);
    q.bindValue(":photo",bytes);
    q.exec();
    photo.close();

    for(uint i=0;i<images_path.size();++i)
    {
        q.exec("select MAX(idpictures) from pictures");
        q.next();
        int idpictures=q.value(0).toInt() + 1;

        q.prepare("insert into pictures values (:idpictures,:description, :idpatient)");
        qDebug()<<idpatient;
        qDebug()<<images_path[i];
        QFile img(images_path[i]);
        img.open(QIODevice::ReadOnly);
        QByteArray bytesimg = img.readAll();
        q.bindValue(":idpictures",idpictures);
        q.bindValue(":idpatient",idpatient);
        q.bindValue(":description",bytesimg);
        q.exec();
        qDebug()<<q.lastError().text();
    }

    q.exec("select MAX(iddiagnoses) from diagnoses");
    q.next();
    int iddiagnoses=q.value(0).toInt() + 1;
    q.prepare("insert into diagnoses values (:iddiagnoses,:name,:idpatient)");
    q.bindValue(":iddiagnoses",iddiagnoses);
    q.bindValue(":name",ui->textEdit->toPlainText());
    q.bindValue(":idpatient",idpatient);
    q.exec();
    qDebug()<<q.lastError().text();
}

void MainWindow::on_loadButton_clicked()
{
    foto_path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                             "/home",
                                             tr("Images (*.png *.xpm *.jpg)"));
    QPixmap img;
    img.load(foto_path,"JPEG");

    scene->addPixmap(img);
}

void MainWindow::on_pushButtonAEP_clicked()
{
    images_path = QFileDialog::getOpenFileNames(this, tr("Open File"),
                                                "/home",
                                                tr("Images (*.png *.xpm *.jpg)"));
    for(uint i=0;i<images_path.size();++i)
    {
        ui->listWidget->addItem(images_path[i]);
    }

    ui->listWidget->setCurrentRow(0);
}

void MainWindow::on_saveButton_clicked()
{
    QSqlQuery q;
    QString first_name = ui->lineEdit1n->text();
    QString last_name = ui->lineEdit2n->text();
    QString patronymic = ui->lineEdit3n->text();
    QString full_name = first_name+" "+last_name+" "+patronymic;
    bool sex;
    if(ui->comboBoxS->currentIndex() == 0)
        sex = 0;
    else
        sex = 1;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    uint unique_val=qrand()%10000;


    q.exec("select MAX(idpatient) from patient");
    q.next();

      int  idpatient=q.value(0).toInt() + 1;

    QString health_insurance_id = ui->lineEditMI->text();
    QString phone_number = ui->lineEditPh->text();
    QString email = ui->lineEditEm->text();
    uint y = ui->spinBoxYr->value();
    uint m = ui->comboBoxM->currentIndex()+1;
    uint d = ui->comboBoxM->currentIndex()+1;
    QDate birth_date = QDate(y,m,d);
    QFile photo(foto_path);
    photo.open(QIODevice::ReadOnly);
    QByteArray bytes = photo.readAll();
    q.prepare("insert into patient(idpatient,fullname,birth_date,sex,health_insurance_id,phone_number,email,photo) values (:idpatient,:fullname,:birth_date,:sex,:health_insurance_id,:phone_number,:email,:photo)");
    q.bindValue(":idpatient",idpatient);
    q.bindValue(":fullname",full_name);
    q.bindValue(":birth_date",birth_date);
    q.bindValue(":sex",sex);
    q.bindValue(":health_insurance_id",health_insurance_id);
    //q.bindValue(":unique_val",unique_val);
    q.bindValue(":phone_number",phone_number);
    q.bindValue(":email",email);
    q.bindValue(":photo",bytes);
    q.exec();
    photo.close();

    for(uint i=0;i<images_path.size();++i)
    {
        q.exec("select MAX(idpictures) from pictures");
        q.next();

         int  idpictures=q.value(0).toInt()+1;

        q.prepare("insert into pictures values (:idpictures,:description, :idpatient)");
        qDebug()<<idpatient;
        qDebug()<<images_path[i];
        QFile img(images_path[i]);
        img.open(QIODevice::ReadOnly);
        QByteArray bytesimg = img.readAll();
        q.bindValue(":idpictures",idpictures);
        q.bindValue(":idpatient",idpatient);
        q.bindValue(":description",bytesimg);
        q.exec();
        qDebug()<<q.lastError().text();
    }

    q.exec("select MAX(iddiagnoses) from diagnoses");
    q.next();
    int iddiagnoses=q.value(0).toInt() + 1;
    q.prepare("insert into diagnoses values (:iddiagnoses,:name,:death, :idpatient)");
    q.bindValue(":iddiagnoses",iddiagnoses);
    int dr = ui->lineEditDR->text().toInt();
    q.bindValue(":death",dr);
    q.bindValue(":name",ui->textEdit->toPlainText());
    q.bindValue(":idpatient",idpatient);
    q.exec();
    qDebug()<<q.lastError().text();
}


void MainWindow::on_addMarkButton_clicked()
{
    MarkingTools * mk = new MarkingTools(this);
    QPixmap pix;
    pix.load(ui->listWidget->currentItem()->text());
    mk->setImage(pix);
    mk->show();

}
