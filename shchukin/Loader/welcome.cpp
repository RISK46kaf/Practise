#include "welcome.h"
#include "ui_welcome.h"
#include <QPainter>

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
}

Welcome::~Welcome()
{
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
    ;//
}
