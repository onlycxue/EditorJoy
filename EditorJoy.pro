#-------------------------------------------------
#
# Project created by QtCreator 2014-06-04T10:28:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EditorJoy
TEMPLATE = app


SOURCES += \
    Block/blockbutton.cpp \
    Block/blocklabel.cpp \
    Block/blockswidget.cpp \
    EditorWidget/editorwidget.cpp \
    JsonManage/jsonhandle.cpp \
    OrnamentalWidget/draglabel.cpp \
    OrnamentalWidget/ornamentalwidget.cpp \
    Main/main.cpp \
    Main/mainwindow.cpp \
    DialogWidget/createdialogwidget.cpp \
    FileManage/exportfile.cpp \
    FileManage/importfile.cpp \
    DialogWidget/targetdialog.cpp \
    DialogWidget/backgrounddialog.cpp \
    DialogWidget/statement.cpp
HEADERS  += \
    Block/blockbutton.h \
    Block/blockitem.h \
    Block/blocklabel.h \
    Block/blockswidget.h \
    EditorWidget/editorwidget.h \
    Global/global.h \
    Global/globaldef.h \
    JsonManage/jsonhandle.h \
    OrnamentalWidget/draglabel.h \
    OrnamentalWidget/ornamentalwidget.h \
    Main/mainwindow.h \
    DialogWidget/createdialogwidget.h \
    FileManage/exportfile.h \
    FileManage/importfile.h \
    DialogWidget/targetdialog.h \
    DialogWidget/backgrounddialog.h \
    DialogWidget/statement.h

RESOURCES += \
    Resource/config.qrc \
    Resource/images.qrc

OTHER_FILES += \
    myRc.rc
RC_FILE += \
    myRc.rc
