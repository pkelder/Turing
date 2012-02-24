#-------------------------------------------------
#
# Project created by QtCreator 2012-02-07T18:09:30
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testtape
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += t_tape.h

SOURCES += maintest.cpp \
        t_tape.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += ../simulation/src/MachineConfig.h \
           ../simulation/src/Simulation.h \
           ../simulation/src/Tape.h \
           ../simulation/src/Transition.h \
           ../simulation/src/State.h

SOURCES += ../simulation/src/MachineConfig.cpp \
           ../simulation/src/State.cpp \
           ../simulation/src/Simulation.cpp \
           ../simulation/src/Tape.cpp \
           ../simulation/src/Transition.cpp

QMAKE_CXXFLAGS = -std=c++0x
