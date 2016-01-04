QT += core
QT -= gui

CONFIG += c++11

TARGET = QtZip
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


    INCLUDEPATH += $$PWD/zlib

unix {
    LIBS += -L$$PWD/zlib -lz
}

win32 {
    LIBS += -L$$PWD/zlib/Windows -lzdll
}


SOURCES += main.cpp \
    zip.cpp

HEADERS += \
    zipreader.h \
    zipwriter.h \
    zconf.h \
    zlib.h
