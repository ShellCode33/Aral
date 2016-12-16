#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T13:08:34
#
#-------------------------------------------------

QT       += core gui
QT       += webengine
QT       += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AralGUI
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    serverhandler.cpp

HEADERS  += mainwindow.h \
    serverhandler.h

FORMS    += mainwindow.ui
