#include "cutter.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>

Cutter::Cutter()
{
    tile_size = QSize(256,256);
    scales_amount = 5;
}

void Cutter::cut(QString image_path)
{
    QImage img;
    qDebug()<<img.load(image_path,"JPEG");
    QFile file("image.xml");
    if ( file.open(QIODevice::ReadWrite) )
    {
        QXmlStreamWriter stream(&file); //xml

        stream.setAutoFormatting(true); //xml
        stream.writeStartElement("image"); //xml

        //stream.writeStartElement("scale"); //xml
        //stream.writeAttribute("value",); //xml



        image_size = img.size();
        QDir dir;
        for(uint i=1;i<=scales_amount;++i)
        {

            dir.mkdir(QString::number(i));
            QImage scaled_img = img.scaled(img.size().width()/i,img.size().height()/i,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            scaled_img.save(QString::number(i)+"/"+"scale="+QString::number(i)+".jpeg","JPEG");
            uint tile_amount_w = scaled_img.size().width() / tile_size.width() +1;
            uint tile_amount_h = scaled_img.size().height() / tile_size.height() +1;
            tile_amount.push_back(QSize(tile_amount_w,tile_amount_h));
            uint shift_x = 0;
            uint shift_y = 0;
            uint last_pixel_y = scaled_img.size().height() - ((tile_amount_h-1) * tile_size.height());
            uint last_pixel_x = scaled_img.size().width() - ((tile_amount_w-1) * tile_size.width());
            for(uint h=0;h<tile_amount_h;++h)
            {
                last_pixel_y = tile_size.height();
                if(h == tile_amount_h-1)
                    last_pixel_y = scaled_img.size().height() - ((tile_amount_h-1) * tile_size.height());
                for(uint w=0;w<tile_amount_w;++w)
                {
                    QImage* tile = new QImage(tile_size,QImage::Format_RGB32);
                    last_pixel_x = tile_size.width();
                    if(w == tile_amount_w-1)
                        last_pixel_x = scaled_img.size().width() - ((tile_amount_w-1) * tile_size.width());


                    for(uint y=0;y<last_pixel_y;++y) //цикл по изобржению
                    {
                        for(uint x=0;x<last_pixel_x;++x)
                        {
                            tile->setPixel(x,y,scaled_img.pixel(x+shift_x,y+shift_y));
                        }
                    }

                    shift_x+=tile->size().width();
                    tile->save(QString::number(i)+"/"+"y="+QString::number(h)+"x="+QString::number(w)+"_"+".jpeg","JPEG");
                    delete tile;
                    tile = NULL;
                }
                shift_y+=tile_size.height();
                shift_x = 0;
            }
            stream.writeStartElement("scale"); //xml
            stream.writeAttribute("value",QString::number(i)); //xml
            stream.writeAttribute("width",QString::number(scaled_img.size().width())); //xml
            stream.writeAttribute("height",QString::number(scaled_img.size().height())); //xml
            stream.writeAttribute("tile_amount_w",QString::number(tile_amount_w)); //xml
            stream.writeAttribute("tile_amount_h",QString::number(tile_amount_h)); //xml
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }


}











/*
        for(uint h=0;h<tile_amount_h;++h)
        {
            last_pixel_y = tile_size.height();
            if(h == tile_amount_h)
                last_pixel_y = scaled_img.size().height()-shift_y;
            for(uint w=0;w<tile_amount_w;++w)
            {
                QImage* tile = new QImage(tile_size,QImage::Format_RGB32);
                last_pixel_x = tile_size.width();
                if(w == tile_amount_w)
                    last_pixel_x = scaled_img.size().width()-shift_x;


                for(uint y=0;y<last_pixel_y;++y) //цикл по изобржению
                {
                    for(uint x=0;x<last_pixel_x;++x)
                    {
                        tile->setPixel(x,y,scaled_img.pixel(x+shift_x,y+shift_y));
                    }
                }



                shift_x+=tile->size().width();
                tile->save(QString::number(i)+"/"+"y="+QString::number(h)+"x="+QString::number(w)+"_"+".jpeg","JPEG");
                delete tile;
                tile = NULL;
            }
            shift_y+=tile_size.height();
            shift_x = 0;
        }
*/
