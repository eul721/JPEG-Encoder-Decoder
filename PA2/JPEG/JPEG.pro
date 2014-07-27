#-------------------------------------------------
#
# Project created by QtCreator 2013-02-24T17:32:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JPEG
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    EncoderDecoder.cpp

HEADERS  += mainwindow.h \
    EncoderDecoder.h

FORMS    += mainwindow.ui

INCLUDEPATH += F:\\opencv\\build\\include

LIBS += -LF:\\opencv\\build\\x86\\vc10\\lib \
     -lopencv_calib3d244d \
    -lopencv_contrib244d \
    -lopencv_core244d \
    -lopencv_features2d244d \
    -lopencv_flann244d \
    -lopencv_gpu244d \
    -lopencv_highgui244d \
    -lopencv_imgproc244d \
    -lopencv_legacy244d \
    -lopencv_ml244d \
    -lopencv_objdetect244d \
    -lopencv_ts244d \
    -lopencv_video244d
