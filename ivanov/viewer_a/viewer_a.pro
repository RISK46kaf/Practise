#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T12:58:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewer_a
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

SOURCES += main.cpp\
        viewer.cpp

HEADERS  += viewer.h

FORMS    += viewer.ui

RESOURCES += \
    myresources.qrc
