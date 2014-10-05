#-------------------------------------------------
#
# Project created by QtCreator 2014-08-24T23:32:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LuaSkillsForQSGSIndex
TEMPLATE = app

INCLUDEPATH += include

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/garbage.cpp \
    src/skill_translator.cpp \
    src/CodeDialog.cpp \
    src/syntaxhighlighter.cpp \
	src/git.cpp

HEADERS  += \
    src/mainwindow.h \
    src/garbage.h \
    src/skill_translator.h \
    src/CodeDialog.h \
    src/syntaxhighlighter.h \
	src/git.h

FORMS    += \
    src/mainwindow.ui \
    src/CodeDialog.ui


win32-msvc*{
    DEFINES += _CRT_SECURE_NO_WARNINGS
    !contains(QMAKE_HOST.arch, x86_64) {
        DEFINES += WIN32
        LIBS += -L"$$_PRO_FILE_PWD_/lib/win/x86"
    } else {
        DEFINES += WIN64
        LIBS += -L"$$_PRO_FILE_PWD_/lib/win/x64"
    }
}
win32-g++{
    DEFINES += WIN32
    LIBS += -L"$$_PRO_FILE_PWD_/lib/win/MinGW"
    DEFINES += GPP
}
winrt{
    DEFINES += _CRT_SECURE_NO_WARNINGS
    DEFINES += WINRT
    LIBS += -L"$$_PRO_FILE_PWD_/lib/winrt/x64"
}
macx{
    DEFINES += MAC
    LIBS += -L"$$_PRO_FILE_PWD_/lib/mac/lib"
}
ios{
    DEFINES += IOS
    CONFIG(iphonesimulator){
        LIBS += -L"$$_PRO_FILE_PWD_/lib/ios/simulator/lib"
    }
    else {
        LIBS += -L"$$_PRO_FILE_PWD_/lib/ios/device/lib"
    }
}
linux{
    DEFINES += LINUX
    !contains(QMAKE_HOST.arch, x86_64) {
        LIBS += -L"$$_PRO_FILE_PWD_/lib/linux/x86"
    }
    else {
        LIBS += -L"$$_PRO_FILE_PWD_/lib/linux/x64"
    }
}

LIBS += -lgit2

TRANSLATIONS += LuaSkillsForQSGSIndex.ts

