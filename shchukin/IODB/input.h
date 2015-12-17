#ifndef INPUT_H
#define INPUT_H

#include <QMainWindow>
#include <ImageFrame/imagewidget.h>
#include <Markers/marker.h>


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

private:
    Ui::Input *ui;
    Core::AnamnesManager* _anamnesManager;
    Core::ProfileManager* _profileManager;
    Core::DataBaseManager* _dbManager;
    ImageWidget* _imageWidget;
    QVector<Marker*> markerList;

    void init();
    void clear();
};

#endif // INPUT_H
