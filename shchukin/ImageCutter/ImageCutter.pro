QT += core
QT -= gui

TARGET = ImageCutter
CONFIG += console
CONFIG -= app_bundle

CONFIG   += c++11

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/Cellar/libgsf/1.14.34/include/libgsf-1
INCLUDEPATH += /usr/local/Cellar/fftw/3.3.4_1/include
INCLUDEPATH += /usr/local/Cellar/imagemagick/6.9.2-4/include/ImageMagick-6
INCLUDEPATH += /usr/local/Cellar/orc/0.4.23/include/orc-0.4
INCLUDEPATH += /usr/local/Cellar/little-cms2/2.7/include
INCLUDEPATH += /usr/local/Cellar/openexr/2.2.0/include/OpenEXR
INCLUDEPATH += /usr/local/Cellar/ilmbase/2.2.0/include/OpenEXR
INCLUDEPATH += /usr/local/Cellar/webp/0.4.3/include
INCLUDEPATH += /usr/local/Cellar/pango/1.38.1/include/pango-1.0
INCLUDEPATH += /usr/local/Cellar/harfbuzz/1.0.4/include/harfbuzz
INCLUDEPATH += /usr/local/Cellar/pango/1.38.1/include/pango-1.0
INCLUDEPATH += /usr/local/Cellar/fontconfig/2.11.1/include
INCLUDEPATH += /usr/local/Cellar/freetype/2.5.3_1/include/freetype2
INCLUDEPATH += /usr/local/Cellar/freetype/2.6_1/include/freetype2
INCLUDEPATH += /usr/local/Cellar/libtiff/4.0.6/include
INCLUDEPATH += /usr/local/Cellar/libpng/1.6.18/include/libpng16
INCLUDEPATH += /usr/local/Cellar/libexif/0.6.21/include
INCLUDEPATH += /usr/local/Cellar/glib/2.46.1/include/glib-2.0
INCLUDEPATH += /usr/local/Cellar/glib/2.46.1/lib/glib-2.0/include
INCLUDEPATH += /usr/local/opt/gettext/include
INCLUDEPATH += /usr/include/libxml2

LIBS +=-L/usr/local/lib
LIBS +=-L/usr/local/lib
LIBS +=-L/usr/local/Cellar/glib/2.46.1/lib
LIBS +=-L/usr/local/opt/gettext/lib -lvips-cpp -lvips -lgobject-2.0 -lglib-2.0 -lintl

TEMPLATE = app

SOURCES += main.cpp \
    cutterrunnable.cpp \
    threadpoolcutter.cpp

HEADERS += \
    cutterrunnable.h \
    threadpoolcutter.h

