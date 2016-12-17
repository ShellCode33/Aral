TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pthread
LIBS += -lpthread

SOURCES += \
    main.cpp \
    ../Common/boat.cpp \
    client.cpp \
    server.cpp \
    beaconshandler.cpp \
    clientshandler.cpp

HEADERS += \
    ../coordinates.h \
    ../Common/boat.h \
    ../Common/packet.h \
    client.h \
    server.h \
    beaconshandler.h \
    clientshandler.h
