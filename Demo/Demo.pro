#-------------------------------------------------
#
# Project created by QtCreator 2013-11-28T11:31:17
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

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
    render.cpp \
    obstacle.cpp \
    deviation.cpp \
    menucontainer.cpp \
    menulevelbutton.cpp \
    menubutton.cpp \
    caillot.cpp \
    chute.cpp \
    boost.cpp \
    gameview.cpp \
    abilitybutton.cpp \
    volumebutton.cpp \
    playpausebutton.cpp \
    closebutton.cpp \
    menuradiobutton.cpp \
    menucheckbox.cpp \
    menuslidercircle.cpp \
    option.cpp \
    bacterie.cpp \
    endgamescreen.cpp \
    endgamebutton.cpp \
    gamesoundplayer.cpp

HEADERS  += mainwindow.h \
    gui.h \
    level.h \
    unit.h \
    mapsquare.h \
    map.h \
    render.h \
    obstacle.h \
    deviation.h \
    menucontainer.h \
    menubutton.h \
    menulevelbutton.h \
    caillot.h \
    chute.h \
    boost.h \
    gameview.h \
    abilitybutton.h \
    volumebutton.h \
    playpausebutton.h \
    closebutton.h \
    menuradiobutton.h \
    menucheckbox.h \
    menuslidercircle.h \
    option.h \
    bacterie.h \
    endgamescreen.h \
    endgamebutton.h \
    gamesoundplayer.h

RESOURCES += \
    temp.qrc

TRANSLATIONS = traduction_fr.ts \
traduction_en.ts
