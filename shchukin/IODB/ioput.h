#ifndef IOPUT_H
#define IOPUT_H

#include <QMainWindow>
#include <ImageFrame/imagewidget.h>
#include <Markers/marker.h>
#include <QPair>

namespace Ui {
class IOput;
}

namespace Core {
class AnamnesManager;
class ProfileManager;
class DataBaseManager;
class Sender;
class Analisator;
}

class IOput : public QMainWindow
{
    Q_OBJECT

public:
    explicit IOput(Core::DataBaseManager* dbManager, bool analisisVer = false,
                   QWidget *parent = 0);
    ~IOput();

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
    Ui::IOput *ui;
    Core::AnamnesManager* _anamnesManager;
    Core::ProfileManager* _profileManager;
    Core::DataBaseManager* _dbManager;
    bool _anlisisVersion;
    ImageWidget* _imageWidget;
    Core::Sender* _sender;
    Core::Analisator* _analisator;
    QRgb currentMarkerColor;
    QVector<QPair<QListWidgetItem*,Marker*> > markerList;
    void init();
    void clear();
    int markerID;
};

#endif // IOPUT_H
