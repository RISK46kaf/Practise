#include "output.h"
#include "ui_output.h"

#include "Core/anamnesmanager.h"
#include "Core/profilemanager.h"
#include "Core/databasemanager.h"
#include <QDebug>

using namespace Core;

Output::Output(Core::DataBaseManager *dbManager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Output), _dbManager(dbManager)
{
    ui->setupUi(this);
    init();
}

void Output::init()
{
    ui->pageProfile->setLayout(ui->verticalLayoutProfile);
    ui->pageMark->setLayout(ui->verticalLayoutMark);
    ui->page_1->setLayout(ui->verticalLayoutAnamnez1);
    ui->page_2->setLayout(ui->verticalLayoutAnamnez2);
    ui->page_3->setLayout(ui->verticalLayoutAnamnez3);
    ui->page_4->setLayout(ui->verticalLayoutAnamnez4);
    ui->frameMtools->setLayout(ui->gridLayoutMtools);
    ui->pageMarkers->setLayout(ui->verticalLayoutMarkers);
    _anamnesManager = new AnamnesManager(this);
    _profileManager = new ProfileManager(this);
    _previewList = new QList<QPair<qint64, QString> >();
    _dbManager->setParent(this);
    qDebug() << "cop" << connect(_dbManager,
            &Core::DataBaseManager::updatePreviewListWidget,
            this,
            &Output::onUpdatePreviewListWidget);
    _dbManager->readPreview(_previewList);
    connect(ui->listWidgetPreview,
            &QListWidget::clicked,
            this,
            [=](QModelIndex modIdx)
            {
                qDebug() << "_previewList->operator [](modIdx.row()).first"
                         << _previewList->operator [](modIdx.row()).first;
                _dbManager->
                        readProfileAndAnamnes(_profileManager,
                                                  _anamnesManager,
                                                  _previewList->operator [](modIdx.row()).first);
            },
            Qt::QueuedConnection
            );
    connect(ui->toolProfile,
            &QToolButton::clicked,
            [=]()
            {
                ui->stackedWidget->setCurrentIndex(0);
            });
    connect(ui->toolAnamnes,
            &QToolButton::clicked,
            [=]()
            {
                ui->stackedWidget->setCurrentIndex(1);
            });

    connect(_anamnesManager,
            &Core::AnamnesManager::dateSinceChanged,
            [=](QDate date)
            {
                ui->dateSince->setDate(date);
                qDebug() << ui->dateSince->date();
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textComplaintChanged,
            [=](QString str)
            {
                ui->textComplaint->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textAnDisChanged,
            [=](QString str)
            {
                ui->textAnDis->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textAnLiChanged,
            [=](QString str)
            {
                ui->textAnLi->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineVenChanged,
            [=](QString str)
            {
                ui->lineVen->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineAlerChanged,
            [=](QString str)
            {
                ui->lineAler->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineAlerChanged,
            [=](QString str)
            {
                ui->lineAler->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::checkNorStChanged,
            [=](bool ch)
            {
                ui->checkNorSt->setChecked(ch);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::linePhysChanged,
            [=](QString str)
            {
                ui->linePhys->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineFoodChanged,
            [=](QString str)
            {
                ui->lineFood->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineSkinChanged,
            [=](QString str)
            {
                ui->lineSkin->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineOedemaChanged,
            [=](QString str)
            {
                ui->lineOedema->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textLimphaChanged,
            [=](QString str)
            {
                ui->textLimpha->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineTemprChanged,
            [=](QString str)
            {
                ui->lineTempr->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineRespRChanged,
            [=](QString str)
            {
                ui->lineRespR->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineThoraxChanged,
            [=](QString str)
            {
                ui->lineThorax->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::linePercussionChanged,
            [=](QString str)
            {
                ui->linePercussion->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textBreathChanged,
            [=](QString str)
            {
                ui->textBreath->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineHeartBordersChanged,
            [=](QString str)
            {
                ui->lineHeartBorders->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineSoniCordisChanged,
            [=](QString str)
            {
                ui->lineSoniCordis->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineArtPreChanged,
            [=](QString str)
            {
                ui->lineArtPre->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::linePulseChanged,
            [=](QString str)
            {
                ui->linePulse->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::linePulse2Changed,
            [=](QString str)
            {
                ui->linePulse2->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineTongueChanged,
            [=](QString str)
            {
                ui->lineTongue->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textStomachChanged,
            [=](QString str)
            {
                ui->textStomach->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textLiverChanged,
            [=](QString str)
            {
                ui->textLiver->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textPasternatskyChanged,
            [=](QString str)
            {
                ui->textPasternatsky->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineFecesChanged,
            [=](QString str)
            {
                ui->lineFeces->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textUrinationChanged,
            [=](QString str)
            {
                ui->textUrination->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textDiagnosisChanged,
            [=](QString str)
            {
                ui->textDiagnosis->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textByComplaintChanged,
            [=](QString str)
            {
                ui->textByComplaint->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textByAnamnesChanged,
            [=](QString str)
            {
                ui->textByAnamnes->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textPlanResChanged,
            [=](QString str)
            {
                ui->textPlanRes->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::textPlanTherChanged,
            [=](QString str)
            {
                ui->textPlanTher->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineIncapacitatedChanged,
            [=](QString str)
            {
                ui->lineIncapacitated->setText(str);
            }
            );
    connect(_anamnesManager,
            &Core::AnamnesManager::lineDocChanged,
            [=](QString str)
            {
                ui->lineDoc->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineMedCardIDChanged,
            [=](QString str)
            {
                ui->lineMedCardID->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::linePSRNChanged,
            [=](QString str)
            {
                ui->linePSRN->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineMedComIDChanged,
            [=](QString str)
            {
                ui->lineMedComID->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineMedValIDChanged,
            [=](QString str)
            {
                ui->lineMedValID->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineSnilsIDChanged,
            [=](QString str)
            {
                ui->lineSnilsID->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineSaleChanged,
            [=](QString str)
            {
                ui->lineSale->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::textSaleChanged,
            [=](QString str)
            {
                ui->textSale->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineNameChanged,
            [=](QString str)
            {
                ui->lineName->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::dateBthChanged,
            [=](QDate date)
            {
                ui->dateBth->setDate(date);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::sexChanged,
            [=](bool ch)
            {
                ui->radioM->setChecked(ch);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineRegRChanged,
            [=](QString str)
            {
                ui->lineRegR->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineDistrRChanged,
            [=](QString str)
            {
                ui->lineDistrR->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineLocRChanged,
            [=](QString str)
            {
                ui->lineLocR->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineStrRChanged,
            [=](QString str)
            {
                ui->lineStrR->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineHomRChanged,
            [=](QString str)
            {
                ui->lineHomR->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineBuilRChanged,
            [=](QString str)
            {
                ui->lineBuilR->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineApRChanged,
            [=](QString str)
            {
                ui->lineApR->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineRegCChanged,
            [=](QString str)
            {
                ui->lineRegC->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineDistrCChanged,
            [=](QString str)
            {
                ui->lineDistrC->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineLocCChanged,
            [=](QString str)
            {
                ui->lineLocC->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineStrCChanged,
            [=](QString str)
            {
                ui->lineStrC->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineHomCChanged,
            [=](QString str)
            {
                ui->lineHomC->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineBuilCChanged,
            [=](QString str)
            {
                ui->lineBuilC->setText(str);
            }
            );
    connect(_profileManager,
            &Core::ProfileManager::lineApCChanged,
            [=](QString str)
            {
                ui->lineApC->setText(str);
            }
            );
//
}

void Output::onUpdatePreviewListWidget()
{
    if(!_previewList->count())
    {
        qDebug() << "go home";
        return;
    }
    qDebug() << "not home";
    ui->listWidgetPreview->clear();
    for(int i = 0; i < _previewList->count(); ++i)
    {
        QListWidgetItem* itm = new QListWidgetItem();
        itm->setText(_previewList->operator [](i).second);
        ui->listWidgetPreview->addItem(itm);
    }
    ui->listWidgetPreview->setFocus();
}

Output::~Output()
{
    delete ui;
}
