#-------------------------------------------------
#
# Project created by QtCreator 2015-11-25T00:58:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MorphCalc
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libopencv_core.3.0.0.dylib
LIBS += /usr/local/lib/libopencv_highgui.3.0.0.dylib
LIBS += /usr/local/lib/libopencv_imgproc.3.0.0.dylib

SOURCES += main.cpp\
        selector.cpp \
    storage.cpp \
    shape.cpp \
    Recognizer/tthing.cpp \
    Recognizer/tregmode.cpp \
    Recognizer/treservationrules.cpp \
    Recognizer/trecognizer.cpp \
    recognizemediator.cpp

HEADERS  += selector.h \
    storage.h \
    shape.h \
    Recognizer/tthing.h \
    Recognizer/tregmode.h \
    Recognizer/treservationrules.h \
    Recognizer/trecognizer.h \
    Recognizer/tlayerrec.h \
    Recognizer/pixrec.h \
    Recognizer/tlayert.h \
    Recognizer/tlayerb.h \
    recognizemediator.h \
    Recognizer/tmatrixt.h

FORMS    += selector.ui
