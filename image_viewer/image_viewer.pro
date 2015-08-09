#-------------------------------------------------
#
# Project created by QtCreator 2015-07-24T16:30:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image_viewer
TEMPLATE = app

#QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

SOURCES += main.cpp\
        viewer.cpp \
    cutter.cpp \
    mygraphicsview.cpp \
    tilemap.cpp \
    tile.cpp \
    Figures/shapebase.cpp \
    Figures/ellipse.cpp \
    Figures/rect.cpp \
    Figures/arrow.cpp \
    Figures/polygon.cpp

HEADERS  += viewer.h \
    cutter.h \
    mygraphicsview.h \
    tilemap.h \
    tile.h \
    Figures/ellipse.h \
    Figures/rect.h \
    Figures/arrow.h \
    Figures/shapebase.h \
    Figures/polygon.h \
    Figures/figures.h

FORMS    += viewer.ui

DISTFILES += \
    NewForm.ui.qml \
    New.qml
