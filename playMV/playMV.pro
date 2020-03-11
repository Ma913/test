#-------------------------------------------------
#
# Project created by QtCreator 2020-02-22T15:31:53
#
#-------------------------------------------------

QT       += core gui
QT +=multimedia
QT +=multimediawidgets
QT +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = playMV
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES += \
    images.qrc
