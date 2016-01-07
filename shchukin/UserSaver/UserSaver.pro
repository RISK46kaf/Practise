#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T20:47:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UserSaver
TEMPLATE = app

CONFIG += c++11

macx {
    INCLUDEPATH += $$PWD/BotanOSX/include
    LIBS += -L$$PWD/BotanOSX -lbotan-1.10
}

win32 {
    INCLUDEPATH += $$PWD/BotanWin/include
    LIBS += -L$$PWD/BotanWin -lbotan
}

SOURCES += main.cpp\
        usersaver.cpp \
    worker.cpp

HEADERS  += usersaver.h \
    worker.h

FORMS    += usersaver.ui

RESOURCES += \
    rsc/resources.qrc
