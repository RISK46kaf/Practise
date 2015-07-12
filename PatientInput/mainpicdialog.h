#ifndef MAINPICDIALOG_H
#define MAINPICDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QModelIndexList>
#include <QStandardItemModel>


namespace Ui {
class MainPicDialog;
}

class MainPicDialog : public QDialog
{
    Q_OBJECT

public:
//    explicit MainPicDialog(QWidget *parent = 0);
    MainPicDialog(QSqlDatabase&DB ,int publicID, QWidget *parent = 0);
    ~MainPicDialog();
    int loadPatientPics();
private:
    Ui::MainPicDialog *ui;
    QStandardItemModel *model;
    QModelIndexList selected;
    QList<QIcon> list_icons;
    QSqlDatabase db;
    int idpublic_info;
    int col_count;
    int pic_count;
};

#endif // MAINPICDIALOG_H
