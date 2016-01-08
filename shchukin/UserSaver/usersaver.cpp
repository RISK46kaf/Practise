#include "usersaver.h"
#include "ui_usersaver.h"

#include <QPainter>
#include <QThread>
#include <QDir>
#include <QPalette>
#include <QFileDialog>
#include "worker.h"

UserSaver::UserSaver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserSaver)
{
    ui->setupUi(this);
    setWindowFlags(
      Qt::WindowTitleHint
    | Qt::WindowMinimizeButtonHint
    | Qt::WindowCloseButtonHint
    | Qt::CustomizeWindowHint);
    ui->lineDir->setText(QDir::homePath());
    _lastCorrectO = QDir::homePath();
    connect(ui->lineDir, &QLineEdit::textChanged,
            [=]()
                {
                    if(!QDir(ui->lineDir->text()).exists())
                    {
                        ui->lineDir->setStyleSheet("QLineEdit { color: red };");
                    }
                    else
                    {
                        QColor col = this->palette().color(QPalette::WindowText);
                        ui->lineDir->setStyleSheet(QString("QLineEdit { color: rgb( %1, %2, %3)};")
                                                   .arg(col.red())
                                                   .arg(col.green())
                                                   .arg(col.blue()));
                        _lastCorrectO = ui->lineDir->text();

                    }
                });
    connect(ui->toolBrowse,
            &QToolButton::clicked,
            [=]()
    {
        QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        _lastCorrectO,
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
        if(!dir.isEmpty())
            ui->lineDir->setText(dir);
    });
    _workThread = new QThread(this);
    connect(this, &UserSaver::destroyed, _workThread, &QThread::quit);
    _worker = new Worker();
    connect(this, &UserSaver::startOperation, _worker, &Worker::startOperation);
    connect(_worker, &Worker::workDone, this,
            [=](){
                    ui->saveButton->setEnabled(true);
                    ui->statusBar->showMessage("Данные успешно сохранены",5000);
                 }
            );
    _worker->moveToThread(_workThread);
    _workThread->start();
    ui->centralWidget->setLayout(ui->verticalLayout);
    connect(ui->saveButton,
            &QPushButton::clicked,
            [=]()
                {
                    ui->saveButton->setEnabled(false);
                    emit startOperation(ui->lineLogin->text(),
                                        ui->linePass->text(),
                                        QFileInfo(ui->lineDir->text()).absoluteFilePath()
                                        );
                }
           );
    connect(ui->checkBox,
            &QCheckBox::clicked,
            [=](bool checked)
                {
                    ui->linePass->setEchoMode(
                                                checked ?
                                                    QLineEdit::Normal :
                                                    QLineEdit::Password
                                              );
                }
           );
}

UserSaver::~UserSaver()
{
    delete ui;
}

void UserSaver::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter p(this);
    QPixmap tmp(":/MyFiles/logo.jpg");
    p.drawPixmap((this->width()-tmp.width())/2,(ui->frame->height()-tmp.height())/2,tmp);
}
