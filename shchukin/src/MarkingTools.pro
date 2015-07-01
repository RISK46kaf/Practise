#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T23:32:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarkingTools
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++1y
CONFIG += c++11

#CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    storage.cpp \
    shape.cpp

HEADERS  += mainwindow.h \
    storage.h \
    shape.h

FORMS    += mainwindow.ui
