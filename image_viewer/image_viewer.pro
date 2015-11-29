#-------------------------------------------------
#
# Project created by QtCreator 2015-07-24T16:30:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image_viewer
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

SOURCES += main.cpp\
        viewer.cpp \
    cutter.cpp \
    mygraphicsview.cpp \
    tilemap.cpp \
    tile.cpp \
    Preview/previewview.cpp\
    Figures/shapebase.cpp \
    Figures/ellipse.cpp \
    Figures/rect.cpp \
    Figures/arrow.cpp \
    Figures/polygon.cpp \
    Figures/figuresmanager.cpp \
    DB/defaultnames.cpp \
    Preview/rectitem.cpp \
    Markers/marker.cpp \
    mygraphicsscene.cpp \
    Markers/abstractfigure.cpp \
    Markers/arrowmarker.cpp

HEADERS  += viewer.h \
    cutter.h \
    mygraphicsview.h \
    tilemap.h \
    tile.h \
    Preview/previewview.h\
    Figures/ellipse.h \
    Figures/rect.h \
    Figures/arrow.h \
    Figures/shapebase.h \
    Figures/polygon.h \
    Figures/figuresmanager.h \
    DB/defaultnames.h \
    Preview/rectitem.h \
    Markers/marker.h \
    mygraphicsscene.h \
    Markers/abstractfigure.h \
    Markers/arrowmarker.h

FORMS    += viewer.ui

DISTFILES += \
    NewForm.ui.qml \
    New.qml
