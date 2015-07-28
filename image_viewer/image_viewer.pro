#-------------------------------------------------
#
# Project created by QtCreator 2015-07-24T16:30:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image_viewer
TEMPLATE = app


SOURCES += main.cpp\
        viewer.cpp \
    cutter.cpp \
    mygraphicsview.cpp \
    tilemap.cpp

HEADERS  += viewer.h \
    cutter.h \
    mygraphicsview.h \
    tilemap.h

FORMS    += viewer.ui
