//    #include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>
#include <iostream>
#include <QSize>
#include <QDebug>

#define CV_PIXEL(type,img,x,y) (((type*)(img->imageData+(y)*img->widthStep))+(x)*img->nChannels)


using namespace std;
using namespace cv;

//IplImage* image = 0;
Mat* image = 0;
//IplImage* src = 0;
//Mat* src = 0;

int main(int argc, char **argv)
{
//    QCoreApplication a(argc, argv);


    const char* filename = 1 < argc ? argv[1] :  "Reg1_54507x35402_Reg1.tif";

    std::string tempo(filename);
    image = new Mat(cv::imread(tempo.c_str()));
    Size sz = image->size();
    qDebug() << "sz w" << sz.width;
    qDebug() << "sz h" << sz.height;
    qDebug() << "sz a" << sz.area();
    //src = cvCloneImage(image);

    printf("[i] image: %s\n", filename);

    uint scales_amount=5;
    QDir dir;
    QSize tile_size = QSize(256,256);
    Mat* scaled_image;
    string path;
    uint tile_amount_w;
    uint tile_amount_h;
    uint shift_x;
    uint shift_y;
    uint last_pixel_y;
    uint last_pixel_x;
    for(uint i=1;i<scales_amount;++i)
    {
        scaled_image = new Mat(image->size(),image->type());

        dir.mkdir(QString::number(i));

        resize(*image, *scaled_image,scaled_image->size());
        qDebug() << "fuck it";
        path = QString::number(i).toStdString()+"/"+ QString::number(i).toStdString() + ".png";
        const char * st = path.c_str();
        std::vector<int> p(3);
        p.push_back(IMWRITE_PNG_STRATEGY_FILTERED);
        p.push_back(50);
        p.push_back(0);

        tile_amount_w = scaled_image->cols / tile_size.width() +1;
        tile_amount_h = scaled_image->rows / tile_size.height() +1;
        shift_x = 0;
        shift_y = 0;
        last_pixel_y = scaled_image->rows - ((tile_amount_h-1) * tile_size.height());
        last_pixel_x = scaled_image->cols - ((tile_amount_w-1) * tile_size.width());

        Mat* tile;
        for(uint h=0;h<tile_amount_h;++h)
        {
            last_pixel_y = tile_size.height();
            if(h == tile_amount_h-1)
                last_pixel_y = scaled_image->rows - ((tile_amount_h-1) * tile_size.height());
            for(uint w=0;w<tile_amount_w;++w)
            {
                tile = new Mat(tile_size.height(),tile_size.width(),image->type());
                last_pixel_x = tile_size.width();
                if(w == tile_amount_w-1)
                    last_pixel_x = scaled_image->cols  - ((tile_amount_w-1) * tile_size.width());


//                for(int y(0);y<_h;++y)
//                {
//                    QRgb* line = reinterpret_cast<QRgb* >(src.scanLine(y));
//                    for(int x(0);x<_w;++x)
//                    {
//                        if(mat.channels()==3)
//                        {
//                            const cv::Vec3b &bgr=mat.at<cv::Vec3b>(y,x);
//                            line[x] = qRgb(bgr.val[2],bgr.val[1],bgr.val[0]);
//                        }
//                        else if(mat.channels()==4)
//                        {
//                            const cv::Vec4b &bgra=mat.at<cv::Vec4b>(y,x);
//                            ///fully opaque pixels should have alpha set to 255/65535.
//                            line[x] = qRgba(bgra.val[2],bgra.val[1],bgra.val[0],bgra[3]*65535);
//                        }
//                        else break;
//                    }
//                }



                for(uint y=0;y<last_pixel_y;++y) //цикл по изобржению
                {
                    for(uint x=0;x<last_pixel_x;++x)
                    {
                        tile->at<double>(y,x)[0] = scaled_image->at<double>(y+shift_y,x+shift_y);
//                        if(tile->channels() == 3) {
//                            const cv::Vec3b &bgr = scaled_image->at<Vec3b>(y+shift_y,x+shift_y);
//                            tile->at<Vec3b>(y,x)[0] = bgr[0];
//                            tile->at<Vec3b>(y,x)[1] = bgr[1];
//                            tile->at<Vec3b>(y,x)[2] = bgr[2];
//                        } else if(tile->channels() == 4) {
//                            const cv::Vec4b &bgra = scaled_image->at<Vec4b>(y+shift_y,x+shift_y);
//                             tile->at<Vec4b>(y,x)[0] = bgra[0];
//                            tile->at<Vec4b>(y,x)[1] = bgra[1];
//                            tile->at<Vec4b>(y,x)[2] = bgra[2];
//                            tile->at<Vec4b>(y,x)[3] = bgra[3];
//                        } else break;
//                        tile->at(y,x) = scaled_image->at(y+shift_y,x+shift_y);
//                        CV_PIXEL(unsigned char, tile, x, y)[0] = CV_PIXEL(unsigned char, scaled_image, x+shift_x, y+shift_y)[0];
//                        CV_PIXEL(unsigned char, tile, x, y)[1] = CV_PIXEL(unsigned char, scaled_image, x+shift_x, y+shift_y)[1];
//                        CV_PIXEL(unsigned char, tile, x, y)[2] = CV_PIXEL(unsigned char, scaled_image, x+shift_x, y+shift_y)[2];
                        //tile->setPixel(x,y,scaled_img.pixel(x+shift_x,y+shift_y));
                    }
                }
                qDebug() << "ok";
                string path1 = QString::number(i).toStdString()+"/"+ "y="+QString::number(h).toStdString()+"x="+QString::number(w).toStdString() + ".png";
                qDebug()<<QString::fromStdString(path1);
                const char * st1 = path1.c_str();
                imwrite(st1, *tile,p );

                shift_x+=tile->cols;
                delete tile;
            }
            shift_y+=tile_size.height();
            shift_x = 0;

            imwrite(st, *scaled_image,p );
//            cvReleaseImage(& scaled_image);
//            delete scaled_image;
        }

        delete scaled_image;

    }

//    cvReleaseImage(& image);
    delete image;
//    cvReleaseImage(&src);

    return 0;
}
