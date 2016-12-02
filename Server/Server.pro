TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    datareceiver.cpp \
    main.cpp \
    ../coordinates.cpp

HEADERS += \
    datareceiver.h \
    ../coordinates.h
