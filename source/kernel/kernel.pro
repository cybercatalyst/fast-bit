include(../common.pri)

TARGET = kernel

SOURCES += extension.cpp \
           genericcontroller.cpp \
           kernel.cpp
HEADERS += extension.h \
           genericcontroller.h \
           kernel.h

LIBS += -L./extensions/arithmetic \
        -L./extensions/cryptographic \
        -L./extensions/photographic \
        -L./extensions/misc \
        -larithmetic \
        -lcryptographic \
        -lphotographic \
        -lmisc

# Hack to set the dependecies - usually this should not be needed..
PRE_TARGETDEPS += extensions/arithmetic/libarithmetic.a \
                  extensions/cryptographic/libcryptographic.a \
                  extensions/photographic/libphotographic.a \
                  extensions/misc/libmisc.a

CODECFORTR = UTF-8
