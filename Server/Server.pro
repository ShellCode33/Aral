TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -std=c++11

SOURCES += \
    coordinates.cpp \
    datareceiver.cpp \
    main.cpp

HEADERS += \
    coordinates.h \
    datareceiver.h
