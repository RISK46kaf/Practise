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
    input.cpp \
    output.cpp \
    Markers/ellipsemarker.cpp \
    Markers/rectmarker.cpp \
    Markers/advancedabstractfigure.cpp \
    Markers/polygonmarker.cpp \
    sender.cpp \
    recognizemediator.cpp \
    Recognizer/trecognizer.cpp \
    Recognizer/tregmode.cpp \
    Recognizer/treservationrules.cpp \
    Recognizer/tthing.cpp

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
    input.h \
    output.h \
    Markers/ellipsemarker.h \
    Markers/rectmarker.h \
    Markers/advancedabstractfigure.h \
    Markers/polygonmarker.h \
    sender.h \
    recognizemediator.h \
    Recognizer/pixrec.h \
    Recognizer/tlayerb.h \
    Recognizer/tlayerrec.h \
    Recognizer/tlayert.h \
    Recognizer/tmatrixt.h \
    Recognizer/trecognizer.h \
    Recognizer/tregmode.h \
    Recognizer/treservationrules.h \
    Recognizer/tthing.h \
    morphdata.h

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
    input.ui \
    output.ui

RESOURCES += \
    rsc/resources.qrc
