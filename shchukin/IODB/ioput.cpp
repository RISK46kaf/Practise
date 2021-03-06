﻿#include "ioput.h"
#include "ui_ioput.h"

#include "Core/anamnesmanager.h"
#include "Core/profilemanager.h"
#include "Core/databasemanager.h"
#include <QDebug>
#include <QColorDialog>
#include "Core/sender.h"
#include "Core/analisator.h"
#include <QMessageBox>

using namespace Core;

IOput::IOput(Core::DataBaseManager *dbManager, bool analisisVer, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IOput), _dbManager(dbManager), _anlisisVersion(analisisVer)
{
    ui->setupUi(this);
    init();
}

void IOput::init()
{
    markerID = 0;
    ui->pageProfile->setLayout(ui->verticalLayoutProfile);
    ui->pageMark->setLayout(ui->verticalLayoutMark);
    ui->page_1->setLayout(ui->verticalLayoutAnamnez1);
    ui->page_2->setLayout(ui->verticalLayoutAnamnez2);
    ui->page_3->setLayout(ui->verticalLayoutAnamnez3);
    ui->page_4->setLayout(ui->verticalLayoutAnamnez4);
    ui->frameMtools->setLayout(ui->gridLayoutMtools);
    _anamnesManager = new AnamnesManager(this);
    _profileManager = new ProfileManager(this);
    _imageWidget = new ImageWidget(this);
//    _imageWidget->setMinimumWidth(800);
//    ui->frame_2->setMinimumWidth(800);
    this->setMinimumWidth(1200);
//    ui->actionSend->setText()

    ui->imageViewLayout->addWidget(_imageWidget);

    _dbManager->setParent(this);

    if(_anlisisVersion)
    {
        _analisator = new Analisator(this);
        _sender = NULL;
    }
    else
    {
        _analisator = NULL;
        _sender = new Sender(this);
    }

    connect(ui->actionSetPersonalData,
            &QAction::triggered,
            [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    }
    );
    connect(ui->actionSetAnamnes,
            &QAction::triggered,
            [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    }
    );
    connect(ui->actionAddMarker,
            &QAction::triggered,
            [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    }
    );
    if(_anlisisVersion)
    {
        ui->actionSend->setText("Анализировать");
        ui->actionSetAnamnes->setEnabled(false);
        ui->actionSetPersonalData->setEnabled(false);
        _imageWidget->setAnalisisVersion();
        ui->stackedWidget->setCurrentIndex(2);
        connect(ui->actionSend,
                &QAction::triggered,
                [=]() {
            QString answer;
            _analisator->startOperation
                    (
                        _imageWidget->getPath(),
                        _dbManager,
                        &markerList,
                        answer
                    );
            QMessageBox::information(this, "Результат Анализа", answer);
        }
        );
    }
    else
        connect(ui->actionSend,
                &QAction::triggered,
                [=]() {
            //        qint64 anamnesId = _dbManager->writeAnamnes(_anamnesManager);
            //        qDebug() <<  anamnesId <<  "profile id" <<
            //                     _dbManager->
            //                     writeProfile(
            //                         _profileManager,
            //                         anamnesId
            //                         );
            _sender->startOperation
                    (
                        _imageWidget->getPath(),
                        _imageWidget->getAbout(),
                        _dbManager,
                        _anamnesManager,
                        _profileManager,
                        &markerList
                    );
        }
        );
    connect(ui->dateSince,
            &QDateEdit::editingFinished,
            [=]() {
        blockSignals(true);
        qDebug() << "data since" << ui->dateSince->date().toString("dd.MM.yyyy");
        _anamnesManager->setDateSince(ui->dateSince->date());
        blockSignals(false);
    }
    );
    connect(ui->textComplaint,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextComplaint(ui->textComplaint->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->textAnDis,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextAnDis(ui->textAnDis->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->textAnLi,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextAnLi(ui->textAnLi->toPlainText());
        blockSignals(false);
    }
    );

    connect(ui->lineVen,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineVen(ui->lineVen->text());
        blockSignals(false);
    }
    );
    connect(ui->lineAler,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineAler(ui->lineAler->text());
        blockSignals(false);
    }
    );
    connect(ui->checkNorSt,
            &QCheckBox::toggled,
            [=](bool checked)
    {
        blockSignals(true);
        _anamnesManager->setCheckNorSt(checked);
        blockSignals(false);
    }
    );
    connect(ui->linePhys,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLinePhys(ui->linePhys->text());
        blockSignals(false);
    }
    );
    connect(ui->lineFood,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineFood(ui->lineFood->text());
        blockSignals(false);
    }
    );
    connect(ui->lineSkin,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineSkin(ui->lineSkin->text());
        blockSignals(false);
    }
    );
    connect(ui->lineOedema,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineOedema(ui->lineOedema->text());
        blockSignals(false);
    }
    );
    connect(ui->textLimpha,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextLimpha(ui->textLimpha->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->lineTempr,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineTempr(ui->lineTempr->text());
        blockSignals(false);
    }
    );
    connect(ui->lineRespR,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineRespR(ui->lineRespR->text());
        blockSignals(false);
    }
    );
    connect(ui->lineThorax,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineThorax(ui->lineThorax->text());
        blockSignals(false);
    }
    );
    connect(ui->linePercussion,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLinePercussion(ui->linePercussion->text());
        blockSignals(false);
    }
    );
    connect(ui->textBreath,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextBreath(ui->textBreath->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->lineHeartBorders,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineHeartBorders(ui->lineHeartBorders->text());
        blockSignals(false);
    }
    );
    connect(ui->lineSoniCordis,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineSoniCordis(ui->lineSoniCordis->text());
        blockSignals(false);
    }
    );
    connect(ui->lineArtPre,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineArtPre(ui->lineArtPre->text());
        blockSignals(false);
    }
    );
    connect(ui->linePulse,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLinePulse(ui->linePulse->text());
        blockSignals(false);
    }
    );
    connect(ui->linePulse2,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLinePulse2(ui->linePulse2->text());
        blockSignals(false);
    }
    );
    connect(ui->lineTongue,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineTongue(ui->lineTongue->text());
        blockSignals(false);
    }
    );
    connect(ui->textStomach,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextStomach(ui->textStomach->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->textLiver,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextLiver(ui->textLiver->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->textPasternatsky,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextPasternatsky(ui->textPasternatsky->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->lineFeces,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineFeces(ui->lineFeces->text());
        blockSignals(false);
    }
    );
    connect(ui->textUrination,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextUrination(ui->textUrination->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->textDiagnosis,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextDiagnosis(ui->textDiagnosis->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->textByComplaint,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextByComplaint(ui->textByComplaint->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->textByAnamnes,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextByAnamnes(ui->textByAnamnes->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->textPlanRes,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextPlanRes(ui->textPlanRes->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->textPlanTher,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setTextPlanTher(ui->textPlanTher->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->lineIncapacitated,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineIncapacitated(ui->lineIncapacitated->text());
        blockSignals(false);
    }
    );
    connect(ui->lineDoc,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _anamnesManager->setLineDoc(ui->lineDoc->text());
        blockSignals(false);
    }
    );
    connect(ui->lineMedCardID,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineMedCardID(ui->lineMedCardID->text());
        blockSignals(false);
    }
    );
    connect(ui->linePSRN,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLinePSRN(ui->linePSRN->text());
        blockSignals(false);
    }
    );
    connect(ui->lineMedComID,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineMedComID(ui->lineMedComID->text());
        blockSignals(false);
    }
    );
    connect(ui->lineMedValID,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineMedValID(ui->lineMedValID->text());
        blockSignals(false);
    }
    );
    connect(ui->lineSnilsID,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineSnilsID(ui->lineSnilsID->text());
        blockSignals(false);
    }
    );
    connect(ui->lineSale,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineSale(ui->lineSale->text());
        blockSignals(false);
    }
    );
    connect(ui->textSale,
            &QTextEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setTextSale(ui->textSale->toPlainText());
        blockSignals(false);
    }
    );
    connect(ui->lineName,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineName(ui->lineName->text());
        blockSignals(false);
    }
    );
    connect(ui->dateBth,
            &QDateEdit::dateChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setDateBth(ui->dateBth->date());
        blockSignals(false);
    }
    );
    connect(ui->radioM,
            &QRadioButton::toggled,
            [=](bool checked)
    {
        blockSignals(true);
        _profileManager->setSex(checked);
        blockSignals(false);
    }
    );
    connect(ui->radioW,
            &QRadioButton::toggled,
            [=](bool checked)
    {
        blockSignals(true);
        _profileManager->setSex(!checked);
        blockSignals(false);
    }
    );
    connect(ui->lineDiagnosisL,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineDiagnL(ui->lineDiagnosisL->text());
        blockSignals(false);
    }
    );
    connect(ui->lineRegR,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineRegR(ui->lineRegR->text());
        blockSignals(false);
    }
    );
    connect(ui->lineDistrR,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineDistrR(ui->lineDistrR->text());
        blockSignals(false);
    }
    );
    connect(ui->lineLocR,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineLocR(ui->lineLocR->text());
        blockSignals(false);
    }
    );
    connect(ui->lineStrR,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineStrR(ui->lineStrR->text());
        blockSignals(false);
    }
    );
    connect(ui->lineHomR,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineHomR(ui->lineHomR->text());
        blockSignals(false);
    }
    );
    connect(ui->lineBuilR,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineBuilR(ui->lineBuilR->text());
        blockSignals(false);
    }
    );
    connect(ui->lineApR,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineApR(ui->lineApR->text());
        blockSignals(false);
    }
    );
    connect(ui->lineRegC,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineRegC(ui->lineRegC->text());
        blockSignals(false);
    }
    );
    connect(ui->lineDistrC,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineDistrC(ui->lineDistrC->text());
        blockSignals(false);
    }
    );
    connect(ui->lineLocC,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineLocC(ui->lineLocC->text());
        blockSignals(false);
    }
    );
    connect(ui->lineStrC,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineStrC(ui->lineStrC->text());
        blockSignals(false);
    }
    );
    connect(ui->lineHomC,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineHomC(ui->lineHomC->text());
        blockSignals(false);
    }
    );
    connect(ui->lineBuilC,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineBuilC(ui->lineBuilC->text());
        blockSignals(false);
    }
    );
    connect(ui->lineApC,
            &QLineEdit::textChanged,
            [=]() {
        blockSignals(true);
        _profileManager->setLineApC(ui->lineApC->text());
        blockSignals(false);
    }
    );
}

void IOput::clear()
{
    ui->dateSince->setDate(QDate::fromString("01.01.2000","dd.MM.yyyy"));
    ui->textComplaint->clear();
    ui->textAnDis->clear();
    ui->textAnLi->clear();
    ui->lineVen->clear();
    ui->lineAler->clear();
    ui->checkNorSt->setChecked(true);
    ui->linePhys->clear();
    ui->lineFood->clear();
    ui->lineSkin->clear();
    ui->lineOedema->clear();
    ui->textLimpha->clear();
    ui->lineTempr->clear();
    ui->lineRespR->clear();
    ui->lineThorax->clear();
    ui->linePercussion->clear();
    ui->linePercussion->clear();
    ui->textBreath->clear();
    ui->lineHeartBorders->clear();
    ui->lineSoniCordis->clear();
    ui->lineArtPre->clear();
    ui->linePulse->clear();
    ui->linePulse2->clear();
    ui->lineTongue->clear();
    ui->textStomach->clear();
    ui->textLiver->clear();
    ui->textPasternatsky->clear();
    ui->lineFeces->clear();
    ui->textUrination->clear();
    ui->textDiagnosis->clear();
    ui->textByComplaint->clear();
    ui->textByAnamnes->clear();
    ui->textPlanRes->clear();
    ui->textPlanTher->clear();
    ui->lineIncapacitated->clear();
    ui->lineDoc->clear();
    ui->lineMedCardID->clear();
    ui->linePSRN->clear();
    ui->lineMedComID->clear();
    ui->lineMedValID->clear();
    ui->lineSnilsID->clear();
    ui->lineSale->clear();
    ui->textSale->clear();
    ui->lineName->clear();
    ui->lineName->clear();
    ui->dateBth->setDate(QDate::fromString("01.01.1902","dd.MM.yyyy"));
    ui->radioM->setChecked(true);
    ui->lineRegR->clear();
    ui->lineDistrR->clear();
    ui->lineLocR->clear();
    ui->lineStrR->clear();
    ui->lineHomR->clear();
    ui->lineBuilR->clear();
    ui->lineApR->clear();
    ui->lineRegC->clear();
    ui->lineDistrC->clear();
    ui->lineLocC->clear();
    ui->lineStrC->clear();
    ui->lineHomC->clear();
    ui->lineBuilC->clear();
    ui->lineApC->clear();
}

IOput::~IOput()
{
    delete ui;
}


void IOput::on_toolArrow_clicked()
{
    for(int i=0;i<markerList.size();++i)
    {
        if(markerList[i].second != NULL)
        {
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(setFirstPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mouseReleasePos(QPoint)),markerList[i].second,SLOT(setScecondPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(addPoint(QPoint)));
        }
    }
    if(_imageWidget)
    {
        Marker* m = new Marker();

        connect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),m,SLOT(setFirstPoint(QPoint)));
        connect(_imageWidget->scene, SIGNAL(mouseReleasePos(QPoint)),m,SLOT(setScecondPoint(QPoint)));
        connect(_imageWidget->map,SIGNAL(scaleChanged(uint)),m,SLOT(setCurrentScale(uint)));

        m->drawArrow();
        m->setFirstScale(_imageWidget->scale);
        m->item->currentScale = _imageWidget->scale;
        _imageWidget->scene->addItem(m->item);
        m->item->setZValue(4);
        _imageWidget->markers.push_back(m);
        m->item->imageRect = _imageWidget->scene->sceneRect();
        m->setWidth(10);
        m->setColor(currentMarkerColor);
        m->item->update();

        QListWidgetItem * item = new QListWidgetItem;
        item->setText(m->name);

        markerList.push_back(qMakePair(item,m));
        ui->listWidget->addItem(item);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }
}

void IOput::on_toolCol_clicked()
{
    currentMarkerColor = QColorDialog::getRgba();
    markerList[ui->listWidget->currentRow()].second->setColor(currentMarkerColor);
}

void IOput::on_toolEllipse_clicked()
{
    qDebug()<<"A";

    for(int i=0;i<markerList.size();++i)
    {
        if(markerList[i].second != NULL)
        {
            qDebug()<<markerList[i].second;
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(setFirstPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mouseReleasePos(QPoint)),markerList[i].second,SLOT(setScecondPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(addPoint(QPoint)));
        }
    }
    qDebug()<<"B";
    if(_imageWidget)
    {
        Marker* m = new Marker();

        connect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),m,SLOT(setFirstPoint(QPoint)));
        connect(_imageWidget->scene, SIGNAL(mouseReleasePos(QPoint)),m,SLOT(setScecondPoint(QPoint)));
        connect(_imageWidget->map,SIGNAL(scaleChanged(uint)),m,SLOT(setCurrentScale(uint)));

        m->drawEllipse();
        m->setFirstScale(_imageWidget->scale);
        m->item->currentScale = _imageWidget->scale;
        _imageWidget->scene->addItem(m->item);
        m->item->setZValue(4);
        _imageWidget->markers.push_back(m);
        //m->item->setScale(1.0);
        m->item->imageRect = _imageWidget->scene->sceneRect();
        m->setWidth(10);
        m->setColor(currentMarkerColor);
        m->item->update();

        QListWidgetItem * item = new QListWidgetItem;
        markerList.push_back(qMakePair(item,m));
        item->setText(m->name);
        ui->listWidget->addItem(item);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        for(int i=0;i<markerList.size();++i)
        {
            qDebug()<<"mark "<<i<<markerList[i];
        }
    }
}

void IOput::on_toolRect_clicked()
{
    for(int i=0;i<markerList.size();++i)
    {
        if(markerList[i].second != NULL)
        {
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(setFirstPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mouseReleasePos(QPoint)),markerList[i].second,SLOT(setScecondPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(addPoint(QPoint)));
        }
    }
    if(_imageWidget)
    {
        Marker* m = new Marker();

        connect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),m,SLOT(setFirstPoint(QPoint)));
        connect(_imageWidget->scene, SIGNAL(mouseReleasePos(QPoint)),m,SLOT(setScecondPoint(QPoint)));
        connect(_imageWidget->map,SIGNAL(scaleChanged(uint)),m,SLOT(setCurrentScale(uint)));

        m->drawRect();
        m->setFirstScale(_imageWidget->scale);
        m->item->currentScale = _imageWidget->scale;
        _imageWidget->scene->addItem(m->item);
        m->item->setZValue(4);
        _imageWidget->markers.push_back(m);
        m->item->setScale(1.0);
        m->item->imageRect = _imageWidget->scene->sceneRect();
        m->setWidth(10);
        m->setColor(currentMarkerColor);
        m->item->update();
        qDebug()<<"markerList.size() "<<markerList.size();

        QListWidgetItem * item = new QListWidgetItem;
        markerList.push_back(qMakePair(item,m));
        item->setText(m->name);
        ui->listWidget->addItem(item);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }
}

void IOput::on_toolPoly_clicked()
{
    for(int i=0;i<markerList.size();++i)
    {
        if(markerList[i].second != NULL)
        {
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(setFirstPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mouseReleasePos(QPoint)),markerList[i].second,SLOT(setScecondPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(addPoint(QPoint)));
        }
    }
    if(_imageWidget)
    {
        Marker* m = new Marker();

        connect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),m,SLOT(addPoint(QPoint)));
        connect(_imageWidget->map,SIGNAL(scaleChanged(uint)),m,SLOT(setCurrentScale(uint)));

        m->drawPolygon();
        qDebug()<<"A";
        m->setFirstScale(_imageWidget->scale);
        qDebug()<<"B";
        m->advancedItem->currentScale = _imageWidget->scale;
        qDebug()<<"C";
        _imageWidget->scene->addItem(m->advancedItem);
        m->advancedItem->setZValue(4);
        _imageWidget->markers.push_back(m);
        m->advancedItem->setScale(1.0);
        qDebug()<<"D";
        m->advancedItem->imageRect = _imageWidget->scene->sceneRect();
        qDebug()<<"E";
        m->setWidth(10);
        m->setColor(currentMarkerColor);
        qDebug()<<"F";
        m->advancedItem->update();


        QListWidgetItem * item = new QListWidgetItem;
        markerList.push_back(qMakePair(item,m));

        item->setText(m->name);
        ui->listWidget->addItem(item);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }
}

void IOput::on_toolConf_clicked()
{
    if(_imageWidget)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setText(markerList.last().second->name);
        ui->listWidget->addItem(item);
    }
}

void IOput::on_listWidget_itemClicked(QListWidgetItem *item)
{
    for(int i=0;i<markerList.size();++i)
    {


        if((markerList[i].first == item)&&(item != NULL))
        {
            qDebug()<<"A";
            qDebug()<<markerList[i].first;
            qDebug()<<markerList[i].second;
            if(markerList[i].second->name == "Polygon")
            {
                qDebug()<<"B";
                connect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(addPoint(QPoint)));
            }
            else
            {
                qDebug()<<"C";
                connect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(setFirstPoint(QPoint)));
                connect(_imageWidget->scene, SIGNAL(mouseReleasePos(QPoint)),markerList[i].second,SLOT(setScecondPoint(QPoint)));
            }
            qDebug()<<"D";
            ui->plainTextEdit->setPlainText(markerList[i].second->text);
            qDebug()<<"E";
        }
    }


}

void IOput::on_plainTextEdit_textChanged()
{
    markerList[ui->listWidget->currentRow()].second->text = ui->plainTextEdit->document()->toPlainText();
}

void IOput::on_toolRem_clicked()
{
    qDebug()<<"currentRow "<<ui->listWidget->currentRow();
    qDebug()<<"markerList.size "<<markerList.size();
    for(int i=0;i<markerList.size();++i)
    {
        if(ui->listWidget->currentItem() == markerList[i].first)
        {
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(setFirstPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mouseReleasePos(QPoint)),markerList[i].second,SLOT(setScecondPoint(QPoint)));
            disconnect(_imageWidget->scene, SIGNAL(mousePressPos(QPoint)),markerList[i].second,SLOT(addPoint(QPoint)));

            _imageWidget->scene->removeItem(markerList[i].second->item);
            ui->listWidget->removeItemWidget(markerList[i].first);
            delete markerList[i].first;
            delete markerList[i].second;
            markerList.removeAt(i);
        }
    }
    for(int i=0;i<markerList.size();++i)
    {
        qDebug()<<"mark "<<i<<markerList[i];
    }
    _imageWidget->view->update();
    _imageWidget->scene->update();
    qDebug()<<"END";
}
