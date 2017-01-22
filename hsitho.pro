# General
TARGET = hsitho
DESTDIR = .
CONFIG += c++11
CONFIG -= app_bundle

# QT Specific
QT += gui
QT += widgets
QT += opengl
QT += core

# Project specific files
SOURCES += ./src/*.cpp \
           ./src/nodes/*.cpp \
           ./nodeEditor/*.cpp
HEADERS += ./include/*.hpp \
           ./include/nodes/*.hpp \
           ./nodeEditor/*.hpp

FORMS += ./ui/mainwindow.ui

INCLUDEPATH += . ./include \
               ./include/nodes \
               ./nodeEditor \
               /usr/local/include
OTHER_FILES += ./shaders/* \
               ./libs/* \
               ./nodeEditor/README.md \
               ./README.md

#LIBS += -L./libs -lnodes

OBJECTS_DIR = ./obj
MOC_DIR = ./moc

DEFINES += NODE_EDITOR_SHARED

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter \
                          -Wno-unused-function
