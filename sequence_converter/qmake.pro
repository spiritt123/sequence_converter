QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

VPATH = src
INCLUDEPATH = include

TARGET = main.out

SOURCES += src/*.cpp

#src/*.cpp
#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

HEADERS += include/*.h

FORMS += \
    mainwindow.ui 

