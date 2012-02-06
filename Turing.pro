######################################################################
# Automatically generated by qmake (1.07a) Wed Jan 18 15:03:39 2012
######################################################################

TEMPLATE = app
CONFIG += qt
DESTDIR = bin
OBJECTS_DIR = .tmp
DEPENDPATH += gui/headers gui/src simulation/headers simulation/src
INCLUDEPATH += . simulation/src

# Input
HEADERS += simulation/src/MachineConfig.h \
           simulation/src/Simulation.h \
           simulation/src/Tape.h \
           simulation/src/Transition.h \
           simulation/src/State.h

SOURCES += simulation/src/MachineConfig.cpp \
           simulation/src/State.cpp \
           simulation/src/Simulation.cpp \
           simulation/src/Tape.cpp \
           simulation/src/Transition.cpp \
           simulation/src/main.cpp

QMAKE_CXXFLAGS = -std=c++0x
