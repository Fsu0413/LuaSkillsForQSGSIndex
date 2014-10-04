#-------------------------------------------------
#
# Project created by QtCreator 2014-08-24T23:32:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LuaSkillsForQSGSIndex
TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/garbage.cpp \
    src/skill_translator.cpp \
    src/CodeDialog.cpp \
    src/syntaxhighlighter.cpp

HEADERS  += \
    src/mainwindow.h \
    src/garbage.h \
    src/skill_translator.h \
    src/CodeDialog.h \
    src/syntaxhighlighter.h

FORMS    += \
    src/mainwindow.ui \
    src/CodeDialog.ui


TRANSLATIONS += LuaSkillsForQSGSIndex.ts

