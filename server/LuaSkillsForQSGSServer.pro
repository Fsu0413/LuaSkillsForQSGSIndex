#-------------------------------------------------
#
# Project created by QtCreator 2014-09-27T23:20:55
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = LuaSkillsForQSGSServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/autoupdate.cpp \
    src/udpcontrol.cpp

HEADERS += \
    src/autoupdate.h \
    src/udpcontrol.h

