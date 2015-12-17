#ifndef IP_MATRIX_H
#define IP_MATRIX_H

//#include <QVector>
#include <QtCore>
#include <typeinfo>


//using std::QVector;

namespace Recognizer {

template<class T>
class TMatrixT
{
        QVector<QVector<T> > data;
        quint64 w; quint64 h;
public:
        typedef T value_type;
        typedef quint64 size_type;
        typedef qint64 difference_type;
        TMatrixT(): w(0), h(0) {}
        TMatrixT(qint64 _w, qint64 _h): w(0), h(0) { resize(_w,_h); }
        TMatrixT(qint64 _w, qint64 _h, T _v): w(0), h(0) { resize(_w,_h,_v); }
        size_type height() const { return h; }
        size_type width() const { return w; }
        void resize(qint64 new_width, qint64 new_height)
        {
          data=QVector<QVector<T> >(new_width,QVector<T>(new_height));
          w=new_width; h=new_height;
        }
        QSize size() const
        {
            return QSize(w,h);
        }

        void resize(qint64 new_width, qint64 new_height, T value)
        {
          data=QVector<QVector<T> >(new_width,QVector<T>(new_height,value));
          w=new_width; h=new_height;
        }

        void resize(const QSize& newsize, T value)
        {
#ifdef __DEBUG
            q__DEBUG() << "new size" << newsize;
#endif
          data=QVector<QVector<T> >(newsize.width(),QVector<T>(newsize.height(),value));
          w=newsize.width(); h=newsize.height();
        }

        value_type& operator()(size_type x, size_type y)
        {
          return data[x][y];
        }
        value_type& operator()(const QPoint& p)
        {
          return data[p.x()][p.y()];
        }
        value_type& Pixel(size_type x, size_type y)
        {
          return data[x][y];
        }
        const value_type& Pixel(size_type x, size_type y) const
        {
#ifdef __DEBUG
            q__DEBUG() << "pixel" << x << w << y << h;
#endif
          return data[x][y];
        }
        value_type& Pixel(const QPoint& p)
        {
#ifdef __DEBUG
            q__DEBUG() << "pixel" << p.x() << w << p.y() << h;
#endif
          return data[p.x()][p.y()];
        }
        const value_type& Pixel(const QPoint& p) const
        {
#ifdef __DEBUG
            q__DEBUG() << "pixel" << p.x() << w << p.y() << h;
#endif
          return data[p.x()][p.y()];
        }
        const value_type& operator()(size_type x, size_type y) const
        {
          return data[x][y];
        }
        bool containsPoint(quint64 x, quint64 y)
        {
            return ( 0 <= x || x < w ) && ( 0 <= y || y < h );
        }
        void clear()
        {
            if(typeid(T) != typeid(bool))
            {
                for(quint64 y = 0; y < h; ++y)
                    for(quint64 x = 0; x < w; ++x)
                    {
                        data[x][y].zero();
                    }
            }
            else
            {
                for(quint64 y = 0; y < h; ++y)
                    for(quint64 x = 0; x < w; ++x)
                    {
                        data[x][y] = T();
                    }
            }
        }
};

}
#endif // IP_MATRIX_H
