TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    coordinates.cpp \
    datasender.cpp \
    clock.cpp \
    moment.cpp

HEADERS += \
    coordinates.h \
    datasender.h \
    clock.h \
    moment.h
