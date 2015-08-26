#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T23:49:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = cutter_opencv
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += C:/opencv-mingw/install/include \
C:/opencv-mingw/install/x86/mingw/bin
LIBS += -LC:/opencv-mingw/install/x86/mingw/bin \
-lopencv_core300 \
-lopencv_imgproc300
LIBS += -LC:/opencv-mingw/install/x86/mingw/lib

LIBS+=C:\\opencv-mingw\\lib\\libopencv_core300.dll.a
LIBS+=C:\\opencv-mingw\\lib\\libopencv_highgui300.dll.a
LIBS+=C:\\opencv-mingw\\lib\\libopencv_imgproc300.dll.a
LIBS+=C:\\opencv-mingw\\lib\\libopencv_ml300.dll.a
LIBS+=C:\\opencv-mingw\\lib\\libopencv_calib3d300.dll.a
LIBS+=C:\\opencv-mingw\\lib\\libopencv_flann300.dll.a
LIBS+=C:\\opencv-mingw\\lib\\libopencv_imgcodecs300.dll.a
