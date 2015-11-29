#ifndef OUTPUT_H
#define OUTPUT_H

#include <QMainWindow>

namespace Ui {
class Output;
}
namespace Core {
class AnamnesManager;
class ProfileManager;
class DataBaseManager;
}

class Output : public QMainWindow
{
    Q_OBJECT

public:
    explicit Output(Core::DataBaseManager* dbManager, QWidget *parent = 0);
    ~Output();

private:
    Ui::Output *ui;
    Core::AnamnesManager* _anamnesManager;
    Core::ProfileManager* _profileManager;
    Core::DataBaseManager* _dbManager;
    QList<QPair<qint64, QString> >* _previewList;
    void init();
private slots:
    void onUpdatePreviewListWidget();
};

#endif // OUTPUT_H
