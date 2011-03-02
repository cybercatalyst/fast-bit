#Includes common configuration for all subdirectory .pro files.
INCLUDEPATH += ../backend \
               ../kernel \
               ../frontend \
               ../application

#WARNINGS += -Wall

TEMPLATE = lib
#CONFIG += staticlib
UI_DIR = uic-temp
MOC_DIR = moc-temp
OBJECTS_DIR = obj-temp
