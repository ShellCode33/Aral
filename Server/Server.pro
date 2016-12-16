TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pthread
LIBS += -lpthread

SOURCES += \
    datareceiver.cpp \
    main.cpp \
    ../coordinates.cpp \
    clienthandler.cpp \
    requesthandler.cpp \
    coordinatebuffer.cpp

HEADERS += \
    datareceiver.h \
    clienthandler.h \
    requesthandler.h \
    coordinatebuffer.h \
    ../coordinates.h
