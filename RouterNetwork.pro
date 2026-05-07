QT -= gui
QT += core

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = RouterNetwork

SOURCES += \
    main.cpp \
    Red.cpp \
    Router.cpp

HEADERS += \
    Red.h \
    Router.h
