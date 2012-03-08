#-------------------------------------------------
#
# Project created by QtCreator 2012-02-02T10:56:13
#
#-------------------------------------------------

QT       += core gui

TARGET = Machine_Turing
TEMPLATE = app

DEPENDPATH += headers/ src/
INCLUDEPATH += . headers/ src/ ../simulation/src/

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/stateitem.cpp \
    src/transitionitem.cpp \
    src/newtransitionwindow.cpp

HEADERS  += headers/mainwindow.h \
    headers/stateitem.h \
    headers/transitionitem.h \
    headers/newtransitionwindow.h \
    headers/transitionitem.h \
    headers/stateitem.h \
    headers/newtransitionwindow.h \
    headers/mainwindow.h \
    headers/eraseme.h

FORMS    += ui/mainwindow.ui \
    ui/newtransitionwindow.ui

RESOURCES += \
    Ressource.qrc
