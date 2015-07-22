#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T23:32:01
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarkingTools
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
#QMAKE_CXXFLAGS += -std=c++14
#CONFIG += c++14

SOURCES += main.cpp\
    storage.cpp \
    shape.cpp \
    mainpicdialog.cpp \
    markingtools.cpp \
    figuresdialog.cpp

HEADERS  += \
    storage.h \
    shape.h \
    mainpicdialog.h \
    markingtools.h \
    figuresdialog.h

FORMS    += \
    mainpicdialog.ui \
    markingtools.ui \
    figuresdialog.ui

RESOURCES += \
    ../resources/resources.qrc
