#include "mainwindow.h"
#include "skill_translator.h"
#include <QApplication>
#include <QTranslator>
#include <QDir>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QTranslator qt_translator;
    qt_translator.load("qt_zh_CN.qm");
    qApp->installTranslator(&qt_translator);

    QTranslator translator;
    translator.load("LuaSkillsForQSGSIndex.qm");
    qApp->installTranslator(&translator);

    QDir d("translate");
    if (d.exists()) {
        foreach (QString s, d.entryList()) {
            if (s.endsWith(".txt")) {
                QFile f("translate/" + s);
                f.open(QIODevice::ReadOnly);
                while (!f.atEnd()) {
                    QString line = f.readLine();
                    line = line.trimmed();
                    QStringList l = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                    if (l.length() == 2)
                        SkillTranslator::insertTranslationPair(l.first(), l.last());
                }
            }
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
