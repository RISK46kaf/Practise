#include "storage.h"
#include <QDebug>

///
/// \brief The Storage class класс области содержащей изображение
///
Storage::Storage(QWidget *parent) :
    QLabel(parent)
{
    setScaledContents(true); // можно масштабировать контенд
    scale_ = 1; // переменная, хранящая масштаб
}
///
/// \brief scaleStorage функция сканирования
/// \param aDirection тип зума
/// \param scaleFactor масштаб
///
void Storage::scaleStorage(ZoomType aDirection, const double &scaleFactor)
{
    scale_ = 1;
    QSize size = this->size();
    qDebug() << "2" << size;
    switch (aDirection) {
    case ZoomIn:
        size *= scaleFactor;
        scale_ *= scaleFactor;
        break;
    case ZoomOut:
        size /= scaleFactor;
        scale_ /= scaleFactor;
        break;
    case NoZoom:
        return;
    default:
        break;
    }
    qDebug() << "3" << size;
    this->resize(size);
    qDebug() << "scaled?" << this->hasScaledContents();
    qDebug() << "4" << this->size();
}
