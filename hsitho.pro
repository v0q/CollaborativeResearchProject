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
SOURCES += ./src/*.cpp
HEADERS += ./include/*.hpp
INCLUDEPATH += ./include
OTHER_FILES += shaders/*

OBJECTS_DIR = ./obj
MOC_DIR = ./moc

DISTFILES += \
    shaders/crystalbeacon.frag \
    shaders/raymarchprimitives.frag
