#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T21:57:15
#
#-------------------------------------------------

QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IODB
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        welcome.cpp \
    Core/anamnesmanager.cpp \
    Core/profilemanager.cpp \
    Core/databasemanager.cpp \
    Markers/ellipsemarker.cpp \
    Markers/rectmarker.cpp \
    Markers/advancedabstractfigure.cpp \
    Markers/polygonmarker.cpp \
    Core/sender.cpp \
    Core/recognizemediator.cpp \
    Core/Recognizer/trecognizer.cpp \
    Core/Recognizer/tregmode.cpp \
    Core/Recognizer/treservationrules.cpp \
    Core/Recognizer/tthing.cpp \
    Core/analisator.cpp \
    ioput.cpp \
    Core/morphdatareal.cpp

SOURCES +=   ImageFrame/Preview/rectitem.cpp \
    ImageFrame/Preview/previewview.cpp \
    ImageFrame/mygraphicsscene.cpp \
    ImageFrame/mygraphicsview.cpp \
    ImageFrame/tile.cpp \
    ImageFrame/tilemap.cpp \
    ImageFrame/imagewidget.cpp

SOURCES +=    Markers/marker.cpp \
    Markers/abstractfigure.cpp \
    Markers/arrowmarker.cpp

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libopencv_core.3.0.0.dylib
LIBS += /usr/local/lib/libopencv_highgui.3.0.0.dylib
LIBS += /usr/local/lib/libopencv_imgproc.3.0.0.dylib

HEADERS  += welcome.h \
    Core/anamnesmanager.h \
    Core/profilemanager.h \
    Core/databasemanager.h \
    Markers/ellipsemarker.h \
    Markers/rectmarker.h \
    Markers/advancedabstractfigure.h \
    Markers/polygonmarker.h \
    Core/sender.h \
    Core/recognizemediator.h \
    Core/Recognizer/pixrec.h \
    Core/Recognizer/tlayerb.h \
    Core/Recognizer/tlayerrec.h \
    Core/Recognizer/tlayert.h \
    Core/Recognizer/tmatrixt.h \
    Core/Recognizer/trecognizer.h \
    Core/Recognizer/tregmode.h \
    Core/Recognizer/treservationrules.h \
    Core/Recognizer/tthing.h \
    Core/analisator.h \
    ioput.h \
    Core/morphdata.h \
    Core/morphdatareal.h

HEADERS  +=    ImageFrame/Preview/previewview.h\
    ImageFrame/Preview/rectitem.h \
    ImageFrame/mygraphicsscene.h \
    ImageFrame/mygraphicsview.h \
    ImageFrame/tile.h \
    ImageFrame/tilemap.h \
    ImageFrame/imagewidget.h

HEADERS  +=    Markers/marker.h \
    Markers/abstractfigure.h \
    Markers/arrowmarker.h

FORMS    += welcome.ui \
    ioput.ui

RESOURCES += \
    rsc/resources.qrc
