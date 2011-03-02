include(../common.pri)

QT += core

SOURCES += frontend.cpp \
	   guiinterface.cpp
HEADERS += frontend.h \
	   guiinterface.h

TARGET = frontend

DESTDIR = ../..
CODECFORTR = UTF-8
