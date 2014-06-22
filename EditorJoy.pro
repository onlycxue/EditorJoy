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
    DialogWidget/statement.cpp \
    Block/blockBase.cpp \
    Block/colorBombBlock.cpp \
    Block/commonBlock.cpp \
    Block/generalBlock.cpp \
    Block/petBlock.cpp \
    JsonManage/jsonprotocol.cpp \
    DialogWidget/createdata.cpp \
    DialogWidget/targetdata.cpp \
    DialogWidget/blockgroupdialog.cpp \
    DialogWidget/groupdata.cpp \
    DialogWidget/groupitem.cpp \
    Block/randomBlock.cpp
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
    DialogWidget/statement.h \
    Block/blockBase.h \
    Block/colorBombBlock.h \
    Block/commonBlock.h \
    Block/generalBlock.h \
    Block/petBlock.h \
    JsonManage/jsonprotocol.h \
    DialogWidget/createdata.h \
    DialogWidget/targetdata.h \
    DialogWidget/blockgroupdialog.h \
    DialogWidget/groupdata.h \
    DialogWidget/groupitem.h \
    Block/randomBlock.h

RESOURCES += \
    resource/config.qrc \
    resource/images.qrc

OTHER_FILES += \
    myRc.rc
RC_FILE += \
    myRc.rc
