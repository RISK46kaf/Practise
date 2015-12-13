#ifndef TLAYERT_H
#define TLAYERT_H

#include <QtCore>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Recognizer {

template <class T>
class TLayerT
{
    typedef cv::Vec<T, 1> Vec1t;
public:
    TLayerT()
    {
        matrix =  new cv::Mat(1,1,cv::DataType<T>::type);
    }
    TLayerT(qint64 W, qint64 H)
    {
        matrix =  new cv::Mat(H,W,cv::DataType<T>::type);
    }

    ~TLayerT() { delete matrix; }

    TLayerT(qint64 W, qint64 H, const T& Pix)
    {
        matrix = new cv::Mat(H,W,cv::DataType<T>::type);
        for(qint64 y = 0; y < H; ++y)
            for(qint64 x = 0; x < W; ++x)
            {
                matrix->at<Vec1t>(y,x)[0] = Pix;
            }
    }

    T* Pixel(qint64 x, qint64 y)
    {
        return matrix->ptr<T>(y) + x;//&(matrix->at<Vec1t>(y,x)[0]);
    }

    const T* Pixel(qint64 x, qint64 y) const
    {
        return matrix->ptr<T>(y) + x;//&(matrix->at<Vec1t>(y,x)[0]);
    }

    T* Pixel(QPoint p)
    {
        return matrix->ptr<T>(p.y()) + p.x();//&(matrix->at<Vec1t>(p.y(),p.x())[0]);
    }

    const T* Pixel(QPoint p) const
    {
        return matrix->ptr<T>(p.y()) + p.x();//&(matrix->at<Vec1t>(p.y(),p.x())[0]);
    }

    void setWH(QSize size)
    {
        cv::resize(*matrix, *matrix, cv::Size(size.width(),size.height()),0,0,CV_INTER_NN);
    }

    void setWH(qint64 width, qint64 height)
    {
        cv::resize(*matrix, *matrix, cv::Size(width,height),0,0,CV_INTER_NN);
    }

    quint64 W() const
    {
        return matrix->cols < 0 ? 0 : matrix->cols;
    }

    quint64 H() const
    {
        return matrix->rows < 0 ? 0 : matrix->rows;
    }

    quint64 width() const
    {
        return matrix->cols < 1 ? 0 : matrix->cols - 1;
    }

    quint64 height() const
    {
        return matrix->rows < 1 ? 0 : matrix->rows;
    }

    qint64 Ws() const
    {
        return matrix->cols;
    }

    qint64 Hs() const
    {
        return matrix->rows;
    }

    qint64 Ws1() const
    {
        return matrix->cols - 1;
    }

    qint64 Hs1() const
    {
        return matrix->rows - 1;
    }

    qint64 PixCount() const
    {
        return Ws()*Hs();
    }

    QSize size() const
    {
        return QSize(matrix->cols,matrix->rows);
    }

    bool containsPoint(int x, int y)
    {
        return ( 0 <= x || x < matrix->cols ) && ( 0 <= y || y < matrix->rows );
    }

    bool containsPoint(QPoint p)
    {
        return ( 0 <= p.x() || p.x() < matrix->cols ) && ( 0 <= p.y() || p.y() < matrix->rows );
    }

    void clear()
    {
        if(cv::DataType<T>::type != cv::DataType<bool>::type)
        {
            for(qint64 y = 0; y < Hs(); ++y)
                for(qint64 x = 0; x < Ws(); ++x)
                {
                    matrix->at<Vec1t>(y,x)[0].zero();
                }
        }
        else
        {
            for(qint64 y = 0; y < Hs(); ++y)
                for(qint64 x = 0; x < Ws(); ++x)
                {
                    matrix->at<Vec1t>(y,x)[0] = T();
                }
        }
    }

private:
    cv::Mat* matrix;
};

}
#endif // TLAYERT_H
