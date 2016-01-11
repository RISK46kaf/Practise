#ifndef INPUT_H
#define INPUT_H

#include <QMainWindow>
#include <ImageFrame/imagewidget.h>
#include <Markers/marker.h>
#include <QPair>

namespace Ui {
class Input;
}

namespace Core {
class AnamnesManager;
class ProfileManager;
class DataBaseManager;
}

class Input : public QMainWindow
{
    Q_OBJECT

public:
    explicit Input(Core::DataBaseManager* dbManager, QWidget *parent = 0);
    ~Input();

private slots:
    void on_toolArrow_clicked();

    void on_toolCol_clicked();

    void on_toolEllipse_clicked();

    void on_toolRect_clicked();

    void on_toolConf_clicked();

    void on_toolPoly_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_plainTextEdit_textChanged();

    void on_toolRem_clicked();

private:
    Ui::Input *ui;
    Core::AnamnesManager* _anamnesManager;
    Core::ProfileManager* _profileManager;
    Core::DataBaseManager* _dbManager;
    ImageWidget* _imageWidget;
    QRgb currentMarkerColor;
    QVector<QPair<QListWidgetItem*,Marker*> > markerList;
    void init();
    void clear();
    int markerID;
};

#endif // INPUT_H
