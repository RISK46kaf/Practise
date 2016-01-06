QT += core
QT -= gui

CONFIG += c++11

TARGET = BotanTest
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/BotanWin/include

LIBS += -L$$PWD/BotanWin -lbotan
#LIBS += $$PWD/Botan/libbotan-1.10.dylib

TEMPLATE = app

SOURCES += main.cpp
