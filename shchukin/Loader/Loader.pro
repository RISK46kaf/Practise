#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T16:20:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

TARGET = Loader
TEMPLATE = app


SOURCES += main.cpp\
    Figures/arrow.cpp \
    Figures/ellipse.cpp \
    Figures/figuresmanager.cpp \
    Figures/polygon.cpp \
    Figures/rect.cpp \
    Figures/shapebase.cpp \
    welcome.cpp \
    loaderwindow.cpp \
    Core/evidencesmanager.cpp \
    MyViewers/mygraphicsview.cpp \
    MyViewers/tilemap.cpp \
    MyViewers/tile.cpp \
    Core/viewersmanager.cpp \
    Core/profilemanager.cpp \
    Core/anamnesmanager.cpp

HEADERS  += \
    Figures/arrow.h \
    Figures/ellipse.h \
    Figures/figuresmanager.h \
    Figures/polygon.h \
    Figures/rect.h \
    Figures/shapebase.h \
    Core/evidencesmanager.h \
    loaderwindow.h \
    welcome.h \
    MyViewers/mygraphicsview.h \
    MyViewers/tilemap.h \
    MyViewers/tile.h \
    Core/viewersmanager.h \
    Core/profilemanager.h \
    Core/anamnesmanager.h

FORMS    += \
    welcome.ui \
    loaderwindow.ui

RESOURCES += \
    rsc/resources.qrc
