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



HEADERS  += welcome.h \
    Core/anamnesmanager.h \
    Core/profilemanager.h \
    Core/databasemanager.h \
    input.h \
    output.h \

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
