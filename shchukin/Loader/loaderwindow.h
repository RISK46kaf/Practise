#ifndef LOADERWINDOW_H
#define LOADERWINDOW_H

#include <QMainWindow>

namespace Ui {
class LoaderWindow;
}

class QTreeWidgetItem;

namespace Core {
class EvidencesManager;
class ViewersManager;
class AnamnesManager;
class ProfileManager;
}

class LoaderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoaderWindow(QWidget *parent = 0);
    ~LoaderWindow();

private slots:
    void on_toolAddRoot_clicked();

    void on_toolAddChild_clicked();

    void on_toolCol_clicked();

    void on_toolRem_clicked();

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_actionOpenImageXml_triggered();

    void on_toolRect_toggled(bool checked);

    void on_toolEllipse_toggled(bool checked);

    void on_toolPoly_toggled(bool checked);

    void on_toolArrow_toggled(bool checked);
    void on_treeWidget_clicked(const QModelIndex &index);

    void on_toolConf_clicked();

    void on_actionMark_triggered();

    void on_toolEdit_clicked();

    void on_toolReM_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_actionSetAnamnes_triggered();

    void on_actionSetPersonalData_triggered();

    void on_actionShowHideRight_triggered();

    void on_actionShowHideBottom_triggered();

    void on_dateSince_editingFinished();

    void on_textComplaint_textChanged();

    void on_textAnDis_textChanged();

    void on_textAnLi_textChanged();

    void on_lineVen_editingFinished();

    void on_lineAler_editingFinished();

    void on_checkNorSt_toggled(bool checked);

    void on_linePhys_editingFinished();

    void on_lineFood_editingFinished();

    void on_lineSkin_editingFinished();

    void on_lineOedema_editingFinished();

    void on_textLimpha_textChanged();

    void on_lineTempr_editingFinished();

    void on_lineRespR_editingFinished();

    void on_lineThorax_editingFinished();

    void on_linePercussion_editingFinished();

    void on_textBreath_textChanged();

    void on_lineHeartBorders_editingFinished();

    void on_lineSoniCordis_editingFinished();

    void on_lineArtPre_editingFinished();

    void on_linePulse_editingFinished();

    void on_linePulse2_editingFinished();

    void on_lineTongue_editingFinished();

    void on_textStomach_textChanged();

    void on_textLiver_textChanged();

    void on_textPasternatsky_textChanged();

    void on_lineFeces_editingFinished();

    void on_textUrination_textChanged();

    void on_textDiagnosis_textChanged();

    void on_textByComplaint_textChanged();

    void on_textByAnamnes_textChanged();

    void on_textPlanRes_textChanged();

    void on_textPlanTher_textChanged();

    void on_lineIncapacitated_editingFinished();

    void on_lineDoc_editingFinished();

    void on_lineMedCardID_editingFinished();

    void on_linePSRN_editingFinished();

    void on_lineMedComID_editingFinished();

    void on_lineMedValID_editingFinished();

    void on_lineSnilsID_editingFinished();

    void on_lineSale_editingFinished();

    void on_textSale_textChanged();

    void on_lineName_editingFinished();

    void on_dateBth_editingFinished();

    void on_radioM_toggled(bool checked);

    void on_lineRegR_editingFinished();

    void on_lineDistrR_editingFinished();

    void on_lineLocR_editingFinished();

    void on_lineStrR_editingFinished();

    void on_lineHomR_editingFinished();

    void on_lineBuilR_editingFinished();

    void on_lineApR_editingFinished();

    void on_lineRegC_editingFinished();

    void on_lineDistrC_editingFinished();

    void on_lineLocC_editingFinished();

    void on_lineStrC_editingFinished();
    void on_lineHomC_editingFinished();

    void on_lineBuilC_editingFinished();


    void on_lineApC_editingFinished();

private:
    Ui::LoaderWindow *ui;
    Core::EvidencesManager* _evidancesManager;
    Core::ViewersManager* _viewersManager;
    Core::AnamnesManager* _anamnesManager;
    Core::ProfileManager* _profileManager;
    int _right;
    int _bottom;

    void showToolName(const QString& name);
};
#endif // LOADERWINDOW_H
