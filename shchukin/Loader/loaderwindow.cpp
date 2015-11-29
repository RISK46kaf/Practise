#include "loaderwindow.h"
#include "ui_loaderwindow.h"

#include "Core/evidencesmanager.h"
#include "Core/viewersmanager.h"
#include "Core/anamnesmanager.h"
#include "Core/profilemanager.h"
#include "Figures/figuresmanager.h"

#include <QListWidgetItem>
#include <QMessageBox>

using namespace Core;

LoaderWindow::LoaderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoaderWindow)
{
    ui->setupUi(this);
    ui->pageProfile->setLayout(ui->verticalLayoutProfile);
//    ui->pageInterview->setLayout();
    ui->pageMark->setLayout(ui->verticalLayoutMark);
    ui->page_1->setLayout(ui->verticalLayoutAnamnez1);
    ui->page_2->setLayout(ui->verticalLayoutAnamnez2);
    ui->page_3->setLayout(ui->verticalLayoutAnamnez3);
    ui->page_4->setLayout(ui->verticalLayoutAnamnez4);
    ui->widget->setLayout(ui->horizontalLayoutView);
    ui->frameMtools->setLayout(ui->gridLayoutMtools);
    ui->pageMarkers->setLayout(ui->verticalLayoutMarkers);
    _evidancesManager = new EvidencesManager(ui->treeWidget);
    _viewersManager = new ViewersManager(ui->horizontalLayoutView,this);
    _viewersManager->figuresManager()->setCurrentColor(_evidancesManager->currentColor());
    QString tmp = QString::number((qint64)ui->treeWidget->currentItem());
    _viewersManager->figuresManager()->setEvidenceKey(tmp);
    _anamnesManager = new AnamnesManager(this);
    _profileManager = new ProfileManager(this);
}

LoaderWindow::~LoaderWindow()
{
    delete ui;
}

void LoaderWindow::on_toolAddRoot_clicked()
{
    _evidancesManager->addRoot(QString("новый главный признак"));
}

void LoaderWindow::on_toolAddChild_clicked()
{
    _evidancesManager->addChild(QString("новый подпризнак"));
}

void LoaderWindow::on_toolCol_clicked()
{
    _evidancesManager->setItemColor();
}

void LoaderWindow::on_toolRem_clicked()
{
    _evidancesManager->removeItem();
}

void LoaderWindow::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    _evidancesManager->itemChanged(item,column);
}

void LoaderWindow::on_actionOpenImageXml_triggered()
{
    _viewersManager->on_actionLoad_Image();
    ui->toolArrow->setChecked(false);
    ui->toolPoly->setChecked(false);
    ui->toolEllipse->setChecked(false);
    ui->toolRect->setChecked(false);
}

void LoaderWindow::on_toolRect_toggled(bool checked)
{
    if(checked)
    {
        ui->toolArrow->setChecked(false);
        ui->toolPoly->setChecked(false);
        ui->toolEllipse->setChecked(false);
        _viewersManager->figuresManager()->setTool(Figures::Tool::RectTool);
        showToolName(ui->toolRect->text().toLower());
    } else statusBar()->showMessage("");
}

void LoaderWindow::on_toolEllipse_toggled(bool checked)
{
    if(checked)
    {
        ui->toolArrow->setChecked(false);
        ui->toolPoly->setChecked(false);
        ui->toolRect->setChecked(false);
        _viewersManager->figuresManager()->setTool(Figures::Tool::EllipseTool);
        showToolName(ui->toolEllipse->text().toLower());

    } else statusBar()->showMessage("");
}

inline void LoaderWindow::showToolName(const QString &name)
{
    statusBar()->showMessage(tr("Выбран инструмент %1").arg(name));
}

void LoaderWindow::on_toolPoly_toggled(bool checked)
{
    if(checked)
    {
        ui->toolArrow->setChecked(false);
        ui->toolEllipse->setChecked(false);
        ui->toolRect->setChecked(false);
        _viewersManager->figuresManager()->setTool(Figures::Tool::PolygonTool);
        showToolName(ui->toolPoly->text().toLower());

    } else statusBar()->showMessage("");
}

void LoaderWindow::on_toolArrow_toggled(bool checked)
{
    if(checked)
    {
        ui->toolEllipse->setChecked(false);
        ui->toolPoly->setChecked(false);
        ui->toolRect->setChecked(false);
        _viewersManager->figuresManager()->setTool(Figures::Tool::ArrowTool);
        showToolName(ui->toolArrow->text().toLower());

    } else statusBar()->showMessage("");
}

void LoaderWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    _evidancesManager->itemColor();
}

void LoaderWindow::on_toolConf_clicked()
{
    blockSignals(true);
    qint64 lastId = _viewersManager->figuresManager()->confirm();
    qDebug() << "lastId" << lastId;
    if(lastId < 0)
    {
        blockSignals(false);
        return;
    }
    QListWidgetItem* item = new QListWidgetItem;
    QString text =  _viewersManager->figuresManager()->stringById(lastId);
    item->setText(text);
    ui->listWidgetMarkers->addItem(item);
    qDebug() << text.mid(text.indexOf("ID:")+3,text.indexOf(";")-2);
    ui->treeWidget->repaint();
    ui->treeWidget->setFocus();
    ui->toolArrow->setChecked(false);
    ui->toolPoly->setChecked(false);
    ui->toolEllipse->setChecked(false);
    ui->toolRect->setChecked(false);
    blockSignals(false);
}

void LoaderWindow::on_actionMark_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void LoaderWindow::on_toolEdit_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void LoaderWindow::on_toolReM_clicked()
{
    QListWidgetItem* item = ui->listWidgetMarkers->currentItem();
    ui->toolArrow->setEnabled(false);
    ui->toolPoly->setEnabled(false);
    ui->toolEllipse->setEnabled(false);
    ui->toolRect->setEnabled(false);
    bool ok = false;
    if(item)
    {
        QString tempT = item->text();
        qint64 id = tempT.mid(tempT.indexOf("ID:")+3,tempT.indexOf(";")-2).toLongLong(&ok);
        ok =  _viewersManager->figuresManager()->removeAt(id);
        if(ok)
        {
            ui->treeWidget->update();
            ui->treeWidget->setFocus();
            ui->listWidgetMarkers->takeItem(id);
            ui->toolArrow->setChecked(false);
            ui->toolPoly->setChecked(false);
            ui->toolEllipse->setChecked(false);
            ui->toolRect->setChecked(false);
            ui->toolArrow->setEnabled(true);
            ui->toolPoly->setEnabled(true);
            ui->toolEllipse->setEnabled(true);
            ui->toolRect->setEnabled(true);
        }
    }
    if(!ok)
        QMessageBox::warning(this,QObject::tr("Ошибка"),
                                     QObject::tr("Снача мышью выберите(кликните на) строку с хэшем фигуры"));
    qDebug() << "ok" << ok;
}

void LoaderWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString tmp = QString::number((qint64)item);
    _viewersManager->figuresManager()->setEvidenceKey(tmp);
    qDebug() << "tmp" << tmp;
}

void LoaderWindow::on_actionSetAnamnes_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void LoaderWindow::on_actionSetPersonalData_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void LoaderWindow::on_actionShowHideRight_triggered()
{
    QList< int > _sizes = ui->splitter->sizes() ;
    if(!_sizes.last())
    {
        _sizes.first() -= _right;
        _sizes.last() += _right;
        ui->splitter->setSizes(_sizes);
        ui->actionShowHideRight->setText("Скрыть правую панель");
    }
    else
    {
        ui->actionShowHideRight->setText("Показать правую панель");
        _right = _sizes.last();
        _sizes.first() += _sizes.last();
        _sizes.last() = 0;
        ui->splitter->setSizes(_sizes);
    }
}

void LoaderWindow::on_actionShowHideBottom_triggered()
{
    QList< int > _sizes = ui->splitter_2->sizes() ;
    if(!_sizes.last())
    {
        _sizes.first() -= _bottom;
        _sizes.last() += _bottom;
        ui->splitter_2->setSizes(_sizes);
        ui->actionShowHideBottom->setText("Скрыть нижнюю панель");
    }
    else
    {
        ui->actionShowHideBottom->setText("Показать нижнюю панель");
        _bottom = _sizes.last();
        _sizes.first() += _sizes.last();
        _sizes.last() = 0;
        ui->splitter_2->setSizes(_sizes);
    }
}

void LoaderWindow::on_dateSince_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setDateSince(ui->dateSince->date().toString());
    blockSignals(false);
}

void LoaderWindow::on_textComplaint_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextComplaint(ui->textComplaint->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_textAnDis_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextAnDis(ui->textAnDis->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_textAnLi_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextAnLi(ui->textAnLi->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_lineVen_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineVen(ui->lineVen->text());
    blockSignals(false);
}

void LoaderWindow::on_lineAler_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineAler(ui->lineAler->text());
    blockSignals(false);
}

void LoaderWindow::on_checkNorSt_toggled(bool checked)
{
    blockSignals(true);
    _anamnesManager->setCheckNorSt(checked);
    blockSignals(false);
}

void LoaderWindow::on_linePhys_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLinePhys(ui->linePhys->text());
    blockSignals(false);
}

void LoaderWindow::on_lineFood_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineFood(ui->lineFood->text());
    blockSignals(false);
}

void LoaderWindow::on_lineSkin_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineSkin(ui->lineSkin->text());
    blockSignals(false);
}

void LoaderWindow::on_lineOedema_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineOedema(ui->lineOedema->text());
    blockSignals(false);
}

void LoaderWindow::on_textLimpha_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextLimpha(ui->textLimpha->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_lineTempr_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineTempr(ui->lineTempr->text());
    blockSignals(false);
}

void LoaderWindow::on_lineRespR_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineRespR(ui->lineRespR->text());
    blockSignals(false);
}

void LoaderWindow::on_lineThorax_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineThorax(ui->lineThorax->text());
    blockSignals(false);
}

void LoaderWindow::on_linePercussion_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLinePercussion(ui->linePercussion->text());
    blockSignals(false);
}

void LoaderWindow::on_textBreath_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextBreath(ui->textBreath->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_lineHeartBorders_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineHeartBorders(ui->lineHeartBorders->text());
    blockSignals(false);
}

void LoaderWindow::on_lineSoniCordis_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineSoniCordis(ui->lineSoniCordis->text());
    blockSignals(false);
}

void LoaderWindow::on_lineArtPre_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineArtPre(ui->lineArtPre->text());
    blockSignals(false);
}

void LoaderWindow::on_linePulse_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLinePulse(ui->linePulse->text());
    blockSignals(false);
}

void LoaderWindow::on_linePulse2_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLinePulse2(ui->linePulse2->text());
    blockSignals(false);
}

void LoaderWindow::on_lineTongue_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineTongue(ui->lineTongue->text());
    blockSignals(false);
}

void LoaderWindow::on_textStomach_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextStomach(ui->textStomach->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_textLiver_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextLiver(ui->textLiver->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_textPasternatsky_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextPasternatsky(ui->textPasternatsky->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_lineFeces_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineFeces(ui->lineFeces->text());
    blockSignals(false);
}

void LoaderWindow::on_textUrination_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextUrination(ui->textUrination->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_textDiagnosis_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextDiagnosis(ui->textDiagnosis->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_textByComplaint_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextByComplaint(ui->textByComplaint->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_textByAnamnes_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextByAnamnes(ui->textByAnamnes->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_textPlanRes_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextPlanRes(ui->textPlanRes->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_textPlanTher_textChanged()
{
    blockSignals(true);
    _anamnesManager->setTextPlanTher(ui->textPlanTher->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_lineIncapacitated_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineIncapacitated(ui->lineIncapacitated->text());
    blockSignals(false);
}

void LoaderWindow::on_lineDoc_editingFinished()
{
    blockSignals(true);
    _anamnesManager->setLineDoc(ui->lineDoc->text());
    blockSignals(false);
}

void LoaderWindow::on_lineMedCardID_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineMedCardID(ui->lineMedCardID->text());
    blockSignals(false);
}

void LoaderWindow::on_linePSRN_editingFinished()
{
    blockSignals(true);
    _profileManager->setLinePSRN(ui->linePSRN->text());
    blockSignals(false);
}

void LoaderWindow::on_lineMedComID_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineMedComID(ui->lineMedComID->text());
    blockSignals(false);
}

void LoaderWindow::on_lineMedValID_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineMedValID(ui->lineMedValID->text());
    blockSignals(false);
}

void LoaderWindow::on_lineSnilsID_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineSnilsID(ui->lineSnilsID->text());
    blockSignals(false);
}

void LoaderWindow::on_lineSale_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineSale(ui->lineSale->text());
    blockSignals(false);
}

void LoaderWindow::on_textSale_textChanged()
{
    blockSignals(true);
    _profileManager->setTextSale(ui->textSale->toPlainText());
    blockSignals(false);
}

void LoaderWindow::on_lineName_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineName(ui->lineName->text());
    blockSignals(false);
}
void LoaderWindow::on_dateBth_editingFinished()
{
    blockSignals(true);
    _profileManager->setDateBth(ui->dateBth->date().toString());
    blockSignals(false);
}

void LoaderWindow::on_radioM_toggled(bool checked)
{
    blockSignals(true);
    _profileManager->setSex(checked);
    blockSignals(false);
}

void LoaderWindow::on_lineRegR_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineRegR(ui->lineRegR->text());
    blockSignals(false);
}

void LoaderWindow::on_lineDistrR_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineDistrR(ui->lineDistrR->text());
    blockSignals(false);
}

void LoaderWindow::on_lineLocR_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineLocR(ui->lineLocR->text());
    blockSignals(false);
}

void LoaderWindow::on_lineStrR_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineStrR(ui->lineStrR->text());
    blockSignals(false);
}

void LoaderWindow::on_lineHomR_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineHomR(ui->lineHomR->text());
    blockSignals(false);
}

void LoaderWindow::on_lineBuilR_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineBuilR(ui->lineBuilR->text());
    blockSignals(false);
}

void LoaderWindow::on_lineApR_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineApR(ui->lineApR->text());
    blockSignals(false);
}

void LoaderWindow::on_lineRegC_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineRegC(ui->lineRegC->text());
    blockSignals(false);
}

void LoaderWindow::on_lineDistrC_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineDistrC(ui->lineDistrC->text());
    blockSignals(false);
}

void LoaderWindow::on_lineLocC_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineLocC(ui->lineLocC->text());
    blockSignals(false);
}

void LoaderWindow::on_lineStrC_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineStrC(ui->lineStrC->text());
    blockSignals(false);
}

void LoaderWindow::on_lineHomC_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineHomC(ui->lineHomC->text());
    blockSignals(false);
}

void LoaderWindow::on_lineBuilC_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineBuilC(ui->lineBuilC->text());
    blockSignals(false);
}

void LoaderWindow::on_lineApC_editingFinished()
{
    blockSignals(true);
    _profileManager->setLineApC(ui->lineApC->text());
    blockSignals(false);
}
