#-------------------------------------------------
#
# Project created by QtCreator 2014-06-04T10:28:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EditorJoy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editorwidget.cpp \
    levelhandle.cpp \
    blockswidget.cpp \
    jsonhandle.cpp \
    blocklabel.cpp \
    ornamentalwidget.cpp \
    blockbutton.cpp \
    draglabel.cpp

HEADERS  += mainwindow.h \
    editorwidget.h \
    levelhandle.h \
    blockswidget.h \
    jsonhandle.h \
    globaldef.h \
    blocklabel.h \
    blockitem.h \
    ornamentalwidget.h \
    blockbutton.h \
    draglabel.h

RESOURCES += \
    images.qrc \
    config.qrc
