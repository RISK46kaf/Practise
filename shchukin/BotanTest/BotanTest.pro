QT += core
QT -= gui

CONFIG += c++11

TARGET = BotanTest
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/Botan/build/include

CONFIG += c++11

macx {
    INCLUDEPATH += $$PWD/BotanOSX/include
    LIBS += -L$$PWD/BotanOSX -lbotan-1.10
}

win32 {
    INCLUDEPATH += $$PWD/BotanWin/include
    LIBS += -L$$PWD/BotanWin -lbotan
}

TEMPLATE = app

SOURCES += main.cpp
