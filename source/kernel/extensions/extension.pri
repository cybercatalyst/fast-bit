#Includes common configuration for all subdirectory .pro files.
INCLUDEPATH += ../.. \
               ../../../frontend

#WARNINGS += -Wall

TEMPLATE = lib
CONFIG += staticlib
UI_DIR = uic-temp
MOC_DIR = moc-temp
OBJECTS_DIR = obj-temp
