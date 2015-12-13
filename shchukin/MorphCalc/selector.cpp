#include "selector.h"
#include "ui_selector.h"
#include <QFileDialog>
#include <QScrollBar>
#ifdef _DEBUG
#include <QDebug>
#endif
#include <opencv2/core/core.hpp>
#include "storage.h"
#include "recognizemediator.h"

Selector::Selector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Selector)
{
    ui->setupUi(this);
    init();
}

Selector::~Selector()
{
    delete ui;
}

void Selector::openImage()
{
    QFileDialog fd(0,tr("Open Image"),QString("%1/Pictures").arg(QDir::homePath()),QString("Images (*.png *.jpeg *.jpg *.bmp *.pbm *.pgm *.ppm *.xbm *.xpm)"));
    fd.setFileMode(QFileDialog::ExistingFile);
    if(fd.exec())
    {
        QString filename(fd.selectedFiles().last());
        if(!_image.load(filename)) return;
        autoZoom();
    }
}

void Selector::autoZoom()
{
    if(_image.isNull()) return;
    _storage->resize(_storage_size);
    QSize imageSize = _image.size();
    double s = 1;
    while(_storage_size.width() * s < imageSize.width() ||
          _storage_size.height() * s < imageSize.height())
    {
        s *= 1.0005;
    }
    _storage->resize(imageSize);
    _storage->setPixmap(_image);
    _storage->scaleStorage(ZoomOut,s);
}

void Selector::init()
{
    setCentralWidget(ui->scrollArea);
    _mediator  = new RecognizeMediator;
    _storage = new Storage;
    _storage->setBackgroundRole(QPalette::Background);
    _storage->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    _storage->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->scrollArea->setWidget(_storage);
    _storage_size = ui->scrollArea->size();
    _storage->resize(_storage_size);
    _arrow_list = new QList<Arrow>;
    _rect_list = new QList<Rect>;
    _ellipse_list = new QList<Ellipse>;
    _polygon_list = new QList<Polygon>;
    _storage->setArrows(_arrow_list);
    _storage->setArrows(_arrow_list);
    _storage->setRects(_rect_list);
    _storage->setEllipses(_ellipse_list);
    _storage->setPolygons(_polygon_list);
    _storage->setScrollArea(ui->scrollArea);
    _storage_size = ui->scrollArea->size();
    connect(ui->actionOpen,
            &QAction::triggered,
            this,
            &Selector::openImage
            );
    connect(ui->actionZoomIn,
            &QAction::triggered,
            this,
            [=]() {
                zoomChange(true);
            }
            );
    connect(ui->actionZoomOut,
            &QAction::triggered,
            this,
            [=]() {
                zoomChange(false);
            }
            );
    connect(ui->actionZoomAuto,
            &QAction::triggered,
            this,
            &Selector::autoZoom
            );
    connect(ui->actionStartSelection,
            &QAction::triggered,
            this,
            [=](bool ch)
            {
                _storage->clear();
                if(ch)
                {
                    _storage->setFocus();
                    _storage->setTool(BoundingBoxTool);
                }
            }
    );
    connect(ui->actionCalcMorph,
            &QAction::triggered,
            this,
            [=]()
            {
                _storage->confirmSelection();
                _storage->clear();
                if(_rect_list->count())
                {
                    while(_rect_list->count() > 1)
                    {
                        _rect_list->pop_front();
                    }
                    _storage->repaint();
                    QRect coord = _rect_list->last().getCoordinates();
                    _mediator->calculate(coord,_image);
#ifdef _DEBUG
                    qDebug() << "calc" << coord;
#endif
                }
            }
    );
    connect(_mediator,
            &RecognizeMediator::result,
            ui->textEdit,
            &QTextEdit::setText
    );
//    _storage->setPixmap(QPixmap::fromImage(img));
}

void Selector::zoomChange(bool in)
{
    if(_image.isNull()) return;
    double s = 1.25;
    _storage->setPixmap(_image);
    if(in) _storage->scaleStorage(ZoomIn,s);
    else _storage->scaleStorage(ZoomOut,s);
    ui->scrollArea->horizontalScrollBar()->setValue(
    (ui->scrollArea->horizontalScrollBar()->maximum()+
     ui->scrollArea->horizontalScrollBar()->minimum())/2);

    ui->scrollArea->verticalScrollBar()->setValue(
    (ui->scrollArea->verticalScrollBar()->maximum()+
     ui->scrollArea->verticalScrollBar()->minimum())/2);
}
