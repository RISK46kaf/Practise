#include "welcome.h"
#include "ui_welcome.h"
#include <QPainter>

#include "input.h"
#include "output.h"
#include "Core/databasemanager.h"

#include <QDebug>

using namespace Core;

Welcome::Welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->verticalLayout);
    ui->lineEditU->selectAll();
    ui->lineEditH->selectAll();
    ui->lineEditP->selectAll();
    setWindowFlags(Qt::Tool
    | Qt::WindowTitleHint
    | Qt::WindowMinimizeButtonHint
    | Qt::WindowCloseButtonHint
    | Qt::CustomizeWindowHint);

    ui->comboBoxMode->addItem(tr("Ввод"));
    ui->comboBoxMode->addItem(tr("Вывод"));
    ui->comboBoxMode->setEditable(true);
//    ui->comboBoxMode->lineEdit()->setDisabled(true);
//    ui->comboBoxMode->lineEdit()->setStyleSheet();
    ui->comboBoxMode->lineEdit()->setReadOnly(true);
    ui->comboBoxMode->lineEdit()->setAlignment(Qt::AlignCenter);
    for (int i = 0; i < ui->comboBoxMode->count(); ++i)
    {
        ui->comboBoxMode->setItemData(i, Qt::AlignHCenter, Qt::TextAlignmentRole);
    }
    _dbManager = new DataBaseManager(this);
    connect(_dbManager,SIGNAL(openMode(int)),this, SLOT(onOpenMode(int)));
    _input = NULL;
    _output = NULL;
//    ui->comboBoxMode->setStyleSheet("QComboBox:item {text-align: center; }");
//    ui->comboBoxMode->lineEdit()->setReadOnly(true);
//    ui->comboBoxMode->lineEdit()->setAlignment(Qt::AlignCenter);
}

Welcome::~Welcome()
{
    if(_input) delete _input;
    if(_output) delete _output;
    delete ui;
}

void Welcome::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter p(this);
    QPixmap tmp(":/MyFiles/logo.jpg");
    p.drawPixmap((this->width()-tmp.width())/2,(ui->frame->height()-tmp.height())/2,tmp);
}

void Welcome::on_pushButton_clicked()
{
    _dbManager->connect(ui->lineEditU->text(),ui->lineEditH->text(),
                        ui->lineEditP->text(),ui->comboBoxMode->currentIndex());
}

void Welcome::onOpenMode(int mode)
{
    qDebug() << "on" << mode;
    if(mode == (int)(Mode::Write) && !_input)
    {
        _input = new Input(_dbManager);
        _input->show();
        close();
    }
    else if(mode == (int)(Mode::Read) && !_output)
    {
        _output = new Output(_dbManager);
        _output->show();
        close();
    }
}

