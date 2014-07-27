QT += core \
    gui \
    opengl \
    testlib \
    script
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
  dockWidgets/Console.cpp \
  dockWidgets/ConsoleInterface.cpp \
  dockWidgets/Graph.cpp \
  dockWidgets/Script.cpp \
  scriptClasses/ScriptFile.cpp \
  scriptClasses/ScriptImage.cpp \
  scriptClasses/ScriptVectorImage.cpp \
  renderers/HistogramOpenGLRenderer.cpp \
  renderers/ImageOpenGLRenderer.cpp \
  renderers/OpenGLRenderer.cpp \
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
  dockWidgets/Console.h \
  dockWidgets/ConsoleInterface.h \
  dockWidgets/Graph.h \
  dockWidgets/Script.h \
  scriptClasses/ScriptFile.h \
  scriptClasses/ScriptImage.h \
  scriptClasses/ScriptVectorImage.h \
  renderers/HistogramOpenGLRenderer.h \
  renderers/ImageOpenGLRenderer.h \
  renderers/OpenGLRenderer.h \
  PluginManagerDialog.h \
  PluginManager.h \
  PluginInterface.h \
  PluginProxy.h

DESTDIR = ..
TRANSLATIONS = ../translations/fast-bit_french.ts \
    ../translations/fast-bit_german.ts \
    ../translations/fast-bit_polish.ts \
    ../translations/fast-bit_turkish.ts \
    ../translations/fast-bit_generic.ts

CODECFORTR = UTF-8

FORMS += PluginManagerDialog.ui
