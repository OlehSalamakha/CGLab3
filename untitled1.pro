#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T16:16:02
#
#-------------------------------------------------

QT       += core gui
QT += opengl
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    glwidget.cpp

HEADERS  += widget.h \
    glwidget.h

FORMS    += widget.ui
