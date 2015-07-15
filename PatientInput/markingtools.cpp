#include "markingtools.h"
#include "ui_markingtools.h"
#include "storage.h"
#include <QDebug>
#include <QString>
#include <QStyleFactory>
#include "mainpicdialog.h"

MarkingTools::MarkingTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MarkingTools)
{
    ui->setupUi(this);
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }"
                        "QPushButton:disabled{color: #353030; }QPushButton::checked{color: #2A82DA; }"
                        "QToolButton:hover{background-color: #2A82DA; } QToolBar QToolButton:checked { background-color: #99FF00; }"
                        "QMainWindow::separator { color: #FFFFFF; }");

    ui->centralWidget->setLayout(ui->horizontalLayout);
    ui->frame->setLayout(ui->gridLayout);
    storage_ = new Storage;
    storage_->setBackgroundRole(QPalette::Background);
    storage_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    storage_->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->scrollArea->setWidget(storage_);
    ui->frame_2->setLayout(ui->verticalLayout);
    storage_size_ = ui->scrollArea->size();
    ui->treeWidget->header() ->close ();
    storage_->resize(storage_size_);
    _arrow_list = new QList<Arrow>;
    _rect_list = new QList<Rect>;
    _ellipse_list = new QList<Ellipse>;
    _polygon_list = new QList<Polygon>;
    ////
    QRect r(1,2,3,4);
    QByteArray ba = serialize(r);
    QString lal;
    lal.append(ba.toBase64());
    QByteArray lol;
    lol = QByteArray::fromBase64(QByteArray().append(lal));
    lal.prepend(";");
    lal.prepend((QByteArray().append("Ell")).toBase64());
    lal.append(";");
    lal.append(QByteArray().append(QString("Color:%1").arg(0x1b85d4)).toBase64());
    qDebug() /*<< deserialize<QRect>(ba)*/ << lal/* << deserialize<QRect>(lol)*/;
    QStringList sl = lal.split(";");
    qDebug() << QByteArray::fromBase64(QByteArray().append(sl[0]));
    qDebug() << deserialize<QRect>(QByteArray() = QByteArray::fromBase64(QByteArray().append(sl[1])));
    qDebug() << QByteArray::fromBase64(QByteArray().append(sl[2]));
    Ellipse el;
    el.setCoordinates(r);
    qDebug() << el.getStrData();
    ////
}

MarkingTools::~MarkingTools()
{
    delete _polygon_list;
    delete _ellipse_list;
    delete _rect_list;
    delete _arrow_list;
    delete storage_;
    delete ui;
}

void MarkingTools::enableDefineButtons()
{
    ui->DefPrepButton->setEnabled(true);
    ui->DefDyeButton->setEnabled(true);
    ui->newEvButton->setEnabled(true);
    ui->chEvButton->setEnabled(true);
    ui->remEvButton->setEnabled(true);
    ui->lineZoomEdit->setEnabled(true);
    ui->checkPartBox->setEnabled(true);
}

void MarkingTools::disableDefineButtons()
{
    ui->DefPrepButton->setEnabled(false);
    ui->DefDyeButton->setEnabled(false);
    ui->newEvButton->setEnabled(false);
    ui->chEvButton->setEnabled(false);
    ui->remEvButton->setEnabled(false);
    ui->lineZoomEdit->setEnabled(false);
    ui->checkPartBox->setEnabled(false);
}

void MarkingTools::openImage()
{
    QFileDialog fd(0,tr("Open Image"),QString("%1/Pictures").arg(QDir::homePath()),QString("Images (*.png *.jpeg *.jpg *.bmp *.pbm *.pgm *.ppm *.xbm *.xpm)"));
    fd.setFileMode(QFileDialog::ExistingFile);
    if(fd.exec())
    {
        QString filename(fd.selectedFiles().last());
        if(!_image.load(filename)) return;
        enableDefineButtons();
        autoZoom();
    }
}

void MarkingTools::autoZoom()
{
    if(_image.isNull()) return;
    storage_->resize(storage_size_);
    QSize imageSize = _image.size();
    double s = 1;
    while(storage_size_.width() * s < imageSize.width() - 210 ||
          storage_size_.height() * s < imageSize.height() - 210)
    {
        s *= 1.0005;
    }
    storage_->resize(imageSize);
    storage_->setPixmap(_image);
    storage_->scaleStorage(ZoomOut,s);
}

void MarkingTools::zoomChange(bool plus)
{
    if(_image.isNull()) return;
    double s = 1.25;
    storage_->setPixmap(_image);
    if(plus) storage_->scaleStorage(ZoomIn,s);
    else storage_->scaleStorage(ZoomOut,s);
    ui->scrollArea->horizontalScrollBar()->setValue(
    (ui->scrollArea->horizontalScrollBar()->maximum()+
     ui->scrollArea->horizontalScrollBar()->minimum())/2);

    ui->scrollArea->verticalScrollBar()->setValue(
    (ui->scrollArea->verticalScrollBar()->maximum()+
     ui->scrollArea->verticalScrollBar()->minimum())/2);
}

void MarkingTools::on_actionOpen_triggered()
{
    openImage();
}

void MarkingTools::on_actionZoomIn_triggered()
{
    zoomChange(true);
}

void MarkingTools::on_actionZoomOut_triggered()
{
    zoomChange(false);
}

void MarkingTools::on_actionZoomAuto_triggered()
{
    storage_size_=QSize(790,595);
    autoZoom();
}

void MarkingTools::on_actionEllipse_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionArrow->setChecked(false);
    //    ui->actionEllipse->setChecked(false);
        ui->actionPolygon->setChecked(false);
        ui->actionRect->setChecked(false);
    }
}

void MarkingTools::on_actionRect_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionArrow->setChecked(false);
        ui->actionEllipse->setChecked(false);
        ui->actionPolygon->setChecked(false);
//        ui->actionRect->setChecked(false);
    }
}

void MarkingTools::on_actionPolygon_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionArrow->setChecked(false);
        ui->actionEllipse->setChecked(false);
//        ui->actionPolygon->setChecked(false);
        ui->actionRect->setChecked(false);
    }
}

void MarkingTools::on_actionArrow_toggled(bool arg1)
{
    if(arg1)
    {
//        ui->actionArrow->setChecked(false);
        ui->actionEllipse->setChecked(false);
        ui->actionPolygon->setChecked(false);
        ui->actionRect->setChecked(false);
    }
}

void MarkingTools::on_checkPartBox_toggled(bool checked)
{
    if(checked)
    {
        qDebug() << "lalal";
//        MainPicDialog mainPic;
//        mainPic.exec();
    }
}

void MarkingTools::setImage(QPixmap img)
{
    _image = img;
    enableDefineButtons();
    autoZoom();
}
