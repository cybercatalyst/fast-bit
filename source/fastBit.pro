QT += core \
    gui \
    opengl \
    testlib \
    script
TARGET = fastBit
TEMPLATE = app
MOC_DIR = temporaryFiles
OBJECTS_DIR = temporaryFiles
SOURCES += sourceFiles/ChainProcessor.cpp \
    sourceFiles/ImageProcessor.cpp \
    sourceFiles/Main.cpp \
    sourceFiles/MainWindow.cpp \
    sourceFiles/ScriptEdit.cpp \
    sourceFiles/ScriptEngine.cpp \
    sourceFiles/ScriptingInterface.cpp \
    sourceFiles/SyntaxHighlighter.cpp \
    sourceFiles/dockWidgets/Console.cpp \
    sourceFiles/dockWidgets/Graph.cpp \
    sourceFiles/dockWidgets/Script.cpp \
    sourceFiles/scriptClasses/ScriptFile.cpp \
    sourceFiles/scriptClasses/ScriptImage.cpp \
    sourceFiles/scriptClasses/ScriptVectorImage.cpp \
    sourceFiles/renderers/HistogramOpenGLRenderer.cpp \
    sourceFiles/renderers/ImageOpenGLRenderer.cpp \
    sourceFiles/renderers/OpenGLRenderer.cpp \
    sourceFiles/PluginManagerDialog.cpp \
    sourceFiles/PluginManager.cpp

HEADERS += headerFiles/ChainProcessor.h \
    headerFiles/ImageProcessor.h \
    headerFiles/Main.h \
    headerFiles/MainWindow.h \
    headerFiles/ScriptEdit.h \
    headerFiles/ScriptEngine.h \
    headerFiles/ScriptingInterface.h \
    headerFiles/SyntaxHighlighter.h \
    headerFiles/dockWidgets/Console.h \
    headerFiles/dockWidgets/Graph.h \
    headerFiles/dockWidgets/Script.h \
    headerFiles/scriptClasses/ScriptFile.h \
    headerFiles/scriptClasses/ScriptImage.h \
    headerFiles/scriptClasses/ScriptVectorImage.h \
    headerFiles/renderers/HistogramOpenGLRenderer.h \
    headerFiles/renderers/ImageOpenGLRenderer.h \
    headerFiles/renderers/OpenGLRenderer.h \
    headerFiles/PluginManagerDialog.h \
    headerFiles/PluginManager.h

DESTDIR = ..
TRANSLATIONS = ../translations/fast-bit_french.ts \
    ../translations/fast-bit_german.ts \
    ../translations/fast-bit_polish.ts \
    ../translations/fast-bit_turkish.ts \
    ../translations/fast-bit_generic.ts

CODECFORTR = UTF-8

FORMS += userInterface/PluginManagerDialog.ui
