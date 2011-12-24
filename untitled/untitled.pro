#-------------------------------------------------
#
# Project created by QtCreator 2011-12-05T13:10:23
#
#-------------------------------------------------

QT       += core

QT       += gui

QT       += xml

TARGET = untitled
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    delaunay.cpp \
    xml.cpp \
    lienzo.cpp \
    mainwindow.cpp \
    dialogacercade.cpp

HEADERS += \
    delaunay.h \
    xml.h \
    lienzo.h \
    mainwindow.h \
    dialogacercade.h

LIBS += -lCGAL

LIBS += -lgmp

FORMS += \
    lienzo.ui \
    mainwindow.ui \
    dialogacercade.ui

RESOURCES += \
    iconos/iconos.qrc
