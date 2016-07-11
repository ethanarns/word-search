#-------------------------------------------------
#
# Project created by QtCreator 2016-07-09T17:48:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Crossedwords
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    reader.cpp

HEADERS  += mainwindow.h \
    reader.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++14

DISTFILES +=
