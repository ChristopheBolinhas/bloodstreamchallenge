#-------------------------------------------------
#
# Project created by QtCreator 2013-11-28T11:31:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gui.cpp \
    level.cpp \
    unit.cpp \
    mapsquare.cpp \
    map.cpp \
    render.cpp

HEADERS  += mainwindow.h \
    gui.h \
    level.h \
    unit.h \
    mapsquare.h \
    map.h \
    render.h

RESOURCES += \
    temp.qrc