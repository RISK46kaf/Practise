#ifndef STORAGE_H
#define STORAGE_H

#include <QLabel>
#include <QScrollArea>

///
/// \brief The ZoomType enum NoZoom = x 1, ZoomIn = x scale, ZoomOut = / scale
///
enum ZoomType {
    NoZoom, // *1
    ZoomIn, // *scale
    ZoomOut // /scale
};
///
/// \brief The Storage class класс области содержащей изображение
///
class Storage : public QLabel
{
    Q_OBJECT
    //масштаб
    double scale_;
public:
    explicit Storage(QWidget *parent = 0);
    ///
    /// \brief scaleStorage функция сканирования
    /// \param aDirection тип зума
    /// \param scaleFactor масштаб
    ///
    void scaleStorage(ZoomType aDirection, const double &scaleFactor);
protected:

signals:

public slots:

};

#endif // STORAGE_H
