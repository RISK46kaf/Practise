#include <QCoreApplication>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>
#include <iostream>
#include <QSize>
#include <QDebug>

#define CV_PIXEL(type,img,x,y) (((type*)(img->imageData+(y)*img->widthStep))+(x)*img->nChannels)

IplImage* image = 0;
IplImage* src = 0;

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char* filename =  "Fronalpstock_big.jpg";
    image = cvLoadImage(filename,1);
    //src = cvCloneImage(image);

    printf("[i] image: %s\n", filename);

    uint scales_amount=5;
    QDir dir;
    QSize tile_size = QSize(256,256);
    for(uint i=1;i<scales_amount;++i)
    {
        dir.mkdir(QString::number(i));
        IplImage* scaled_image = cvCreateImage( cvSize(image->width/i, image->height/i), image->depth, image->nChannels );
        cvResize(image, scaled_image);
        string path = QString::number(i).toStdString()+"/"+ QString::number(i).toStdString() + ".jpeg";
        const char * st = path.c_str();
        int p[3];
        p[0] = CV_IMWRITE_JPEG_QUALITY;
        p[1] = 50;
        p[2] = 0;

        uint tile_amount_w = scaled_image->width / tile_size.width() +1;
        uint tile_amount_h = scaled_image->height / tile_size.height() +1;
        uint shift_x = 0;
        uint shift_y = 0;
        uint last_pixel_y = scaled_image->height - ((tile_amount_h-1) * tile_size.height());
        uint last_pixel_x = scaled_image->width - ((tile_amount_w-1) * tile_size.width());

        for(uint h=0;h<tile_amount_h;++h)
        {
            last_pixel_y = tile_size.height();
            if(h == tile_amount_h-1)
                last_pixel_y = scaled_image->height - ((tile_amount_h-1) * tile_size.height());
            for(uint w=0;w<tile_amount_w;++w)
            {
                IplImage* tile = cvCreateImage( cvSize(256, 256), image->depth, image->nChannels );
                last_pixel_x = tile_size.width();
                if(w == tile_amount_w-1)
                    last_pixel_x = scaled_image->width  - ((tile_amount_w-1) * tile_size.width());


                for(uint y=0;y<last_pixel_y;++y) //цикл по изобржению
                {
                    for(uint x=0;x<last_pixel_x;++x)
                    {
                        CV_PIXEL(unsigned char, tile, x, y)[0] = CV_PIXEL(unsigned char, scaled_image, x+shift_x, y+shift_y)[0];
                        CV_PIXEL(unsigned char, tile, x, y)[1] = CV_PIXEL(unsigned char, scaled_image, x+shift_x, y+shift_y)[1];
                        CV_PIXEL(unsigned char, tile, x, y)[2] = CV_PIXEL(unsigned char, scaled_image, x+shift_x, y+shift_y)[2];
                        //tile->setPixel(x,y,scaled_img.pixel(x+shift_x,y+shift_y));
                    }
                }
                string path1 = QString::number(i).toStdString()+"/"+ "y="+QString::number(h).toStdString()+"x="+QString::number(w).toStdString() + ".jpeg";
                qDebug()<<QString::fromStdString(path1);
                const char * st1 = path1.c_str();
                cvSaveImage(st1, tile,p );

                shift_x+=tile->width;
                cvReleaseImage(& tile);
            }
            shift_y+=tile_size.height();
            shift_x = 0;

        }

        cvSaveImage(st, scaled_image,p );
        cvReleaseImage(& scaled_image);

    }

    cvReleaseImage(& image);
    cvReleaseImage(&src);

    return a.exec();
}
