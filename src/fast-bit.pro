QT += \
    core \
    gui \
    opengl \
    testlib \
    script \
    widgets
TARGET = fastbit
TEMPLATE = app
MOC_DIR = temporaryFiles
OBJECTS_DIR = temporaryFiles
SOURCES += \
    ChainProcessor.cpp \
    ImageProcessor.cpp \
    Main.cpp \
    MainWindow.cpp \
    ScriptEdit.cpp \
    ScriptEngine.cpp \
    ScriptingInterface.cpp \
    SyntaxHighlighter.cpp \
    Console.cpp \
    ConsoleInterface.cpp \
    Graph.cpp \
    Script.cpp \
    ScriptFile.cpp \
    ScriptImage.cpp \
    ScriptVectorImage.cpp \
    HistogramOpenGLRenderer.cpp \
    ImageOpenGLRenderer.cpp \
    OpenGLRenderer.cpp \
    PluginManagerDialog.cpp \
    PluginManager.cpp \
    PluginInterface.cpp \
    PluginProxy.cpp

HEADERS += \
    ChainProcessor.h \
    ImageProcessor.h \
    Main.h \
    MainWindow.h \
    ScriptEdit.h \
    ScriptEngine.h \
    ScriptingInterface.h \
    SyntaxHighlighter.h \
    Console.h \
    ConsoleInterface.h \
    Graph.h \
    Script.h \
    ScriptFile.h \
    ScriptImage.h \
    ScriptVectorImage.h \
    HistogramOpenGLRenderer.h \
    ImageOpenGLRenderer.h \
    OpenGLRenderer.h \
    PluginManagerDialog.h \
    PluginManager.h \
    PluginInterface.h \
    PluginProxy.h

DESTDIR = ..

TRANSLATIONS = \
    ../translations/fast-bit_french.ts \
    ../translations/fast-bit_german.ts \
    ../translations/fast-bit_polish.ts \
    ../translations/fast-bit_turkish.ts \
    ../translations/fast-bit_generic.ts

CODECFORTR = UTF-8

FORMS += PluginManagerDialog.ui
