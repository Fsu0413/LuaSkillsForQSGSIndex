#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QTranslator qt_translator;
    qt_translator.load("qt_zh_CN.qm");
    qApp->installTranslator(&qt_translator);

    QTranslator translator;
    translator.load("LuaSkillsForQSGSIndex.qm");
    qApp->installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
