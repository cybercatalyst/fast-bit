include(../common.pri)
QT += core gui opengl testlib script

# Override default settings in common.pri.
TARGET = fast-bit
TEMPLATE = app

LIBS += -L../backend \
        -L../kernel \
        -L../frontend \
	-lbackend \
	-lkernel \
	-lfrontend

SOURCES += application.cpp \
           controller.cpp \
           userinterface.cpp
HEADERS += application.h \
           controller.h \
           userinterface.h

DESTDIR = ../..

# Hack to set the dependecies - usually this should not be needed..
PRE_TARGETDEPS += ../backend/libbackend.a \
                  ../kernel/libkernel.a \
                  ../frontend/libfrontend.a

CODECFORTR = UTF-8
