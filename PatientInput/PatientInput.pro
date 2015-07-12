#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T15:06:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PatientInput
TEMPLATE = app


QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp\
        welcome.cpp \
    mainpicdialog.cpp \
    markingtools.cpp \
    shape.cpp \
    storage.cpp

HEADERS  += mainwindow.h\
           welcome.h \
    mainpicdialog.h \
    markingtools.h \
    shape.h \
    storage.h

FORMS    += mainwindow.ui\
            welcome.ui \
    mainpicdialog.ui \
    markingtools.ui


RESOURCES += \
    myresources.qrc
