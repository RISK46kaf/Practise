#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T15:06:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PatientInput
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        welcome.cpp

HEADERS  += mainwindow.h\
           welcome.h

FORMS    += mainwindow.ui\
            welcome.ui


RESOURCES += \
    myresources.qrc
