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
    socketmanager.cpp \
    udpreceiver.cpp

HEADERS += \
    ../coordinates.h \
    ../Common/boat.h \
    ../Common/packet.h \
    client.h \
    socketmanager.h \
    udpreceiver.h
