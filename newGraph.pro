#-------------------------------------------------
#
# Project created by QtCreator 2016-05-10T14:03:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newGraph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabclass.cpp \
    makegrid.cpp \
    makeselected.cpp \
    drawcrosses.cpp \
    twidget.cpp \
    operationstore.cpp \
    commands.cpp

HEADERS  += mainwindow.h \
    tabclass.h \
    makegrid.h \
    makeselected.h \
    drawcrosses.h \
    twidget.h \
    operationstore.h \
    commands.h \
    twoheaders.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

DISTFILES +=
