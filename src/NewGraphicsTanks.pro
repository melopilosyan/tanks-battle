#-------------------------------------------------
#
# Project created by QtCreator 2011-11-05T14:14:42
#
#-------------------------------------------------

QT       += core gui
# \    phonon

TARGET = NewGraphicsTanks
TEMPLATE = app


SOURCES += sources/main.cpp \
    sources/battleground.cpp \
    sources/bulletItem.cpp \
    sources/tankItem.cpp \
    sources/tanks.cpp \
#    sources/explosionItem.cpp \
    sources/barrierItem.cpp \
    sources/greetingScene.cpp \
    sources/tanksScene.cpp \
    sources/tanksView.cpp


HEADERS  += \
    headers/battleground.h \
    headers/bulletItem.h \
    headers/neededTypes.h \
    headers/tankItem.h \
    headers/tanks.h \
#    headers/explosionItem.h \
    headers/barrierItem.h \
    headers/greetingScene.h \
    headers/tanksScene.h \
    headers/tanksView.h

RESOURCES += \
    resurse.qrc
