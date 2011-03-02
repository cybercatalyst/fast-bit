include(../common.pri)
QT += core gui opengl testlib script

# Override default settings in common.pri.
TARGET = fast-bit
TEMPLATE = app

LIBS += -L../backend \
        -L../kernel \
        -L../frontend

SOURCES += application.cpp
HEADERS += application.h

DESTDIR = ../..

CODECFORTR = UTF-8
