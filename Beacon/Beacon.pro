TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    datasender.cpp \
    clock.cpp \
    moment.cpp \
    ../coordinates.cpp

HEADERS += \
    coordinates.h \
    clock.h \
    moment.h \
    ../coordinates.h \
    datasender.h
