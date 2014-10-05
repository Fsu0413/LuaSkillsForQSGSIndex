#include "mainwindow.h"
#include "skill_translator.h"
#include "git.h"
#include <QApplication>
#include <QTranslator>
#include <QDir>
#include <QMessageBox>

using namespace GitManager;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QTranslator qt_translator;
    qt_translator.load("qt_zh_CN.qm");
    qApp->installTranslator(&qt_translator);

    QTranslator translator;
    translator.load("LuaSkillsForQSGSIndex.qm");
    qApp->installTranslator(&translator);

    QDir git_dir("git/.git");
    bool succeed = false;
    if (git_dir.exists())
        succeed = pull();
    else
        succeed = clone();


    if (!succeed) {
        QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Git Repo Error"));
        return 1;
    }

    QDir translation_dir("git/translations");
    if (translation_dir.exists()) {
        foreach (QString s, translation_dir.entryList()) {
            if (s.endsWith(".txt")) {
                QFile f("git/translations/" + s);
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
