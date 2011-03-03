include(../common.pri)

TARGET = kernel

SOURCES += extension.cpp \
           genericcontroller.cpp \
           kernel.cpp
HEADERS += extension.h \
           genericcontroller.h \
           kernel.h

CODECFORTR = UTF-8
