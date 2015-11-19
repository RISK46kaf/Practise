#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T21:57:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IODB
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        welcome.cpp \
    Core/anamnesmanager.cpp \
    Core/profilemanager.cpp \
    Core/databasemanager.cpp \
    input.cpp \
    output.cpp

HEADERS  += welcome.h \
    Core/anamnesmanager.h \
    Core/profilemanager.h \
    Core/databasemanager.h \
    input.h \
    output.h

FORMS    += welcome.ui \
    input.ui \
    output.ui

RESOURCES += \
    rsc/resources.qrc
