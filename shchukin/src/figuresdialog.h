#ifndef FIGURESDIALOG_H
#define FIGURESDIALOG_H

#include <QDialog>
#include "shape.h"

namespace Ui {
class FiguresDialog;
}

class FiguresDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FiguresDialog(QWidget *parent = 0);
    ~FiguresDialog();
    void setList(QList<Arrow> *,QList<Rect> *,QList<Ellipse> *,QList<Polygon> *);

private:
    Ui::FiguresDialog *ui;
};

#endif // FIGURESDIALOG_H
