#include <QDir>
#include <QMessageBox>
#include "garbage.h"
#include <QApplication>


Garbage *Garbage::instance = NULL;

Garbage *Garbage::getInstance() {
    if (instance == NULL)
        instance = new Garbage;

    return instance;
}

void Garbage::destroyInstancce() {
    if (instance != NULL)
        delete instance;
}

Garbage::Garbage() {
    setObjectName("Garbage");

    QDir dir("skills");
    if (dir.exists()){
        QFileInfoList files = dir.entryInfoList(QDir::Files, QDir::Name);
        foreach (QFileInfo f, files) {
            QString name = f.fileName();
            if (name.endsWith(".txt"))
                new Package(name.left(name.length() - 4), this);
        }
    }

    connect(qApp, &QApplication::aboutToQuit, &Garbage::deleteLater);
}

Package::Package(const QString &name, Garbage *garbage) {
    setObjectName(name);
    setParent(garbage);

    QFile file("skills/" + name + ".txt");
    if (!file.exists() || !exportGenerals(file)) {
        QMessageBox::critical(NULL, tr("Error"), QString(tr("Cannot read file %1")).arg(name + ".txt"));
        delete this;
    }
}

bool Package::exportGenerals(QFile &file) {
    QStringList generals;
    QStringList kingdoms;
    QList<QMap<QString, QString> > skills;

    file.open(QIODevice::ReadOnly);

    while (!file.atEnd()) {
        QRegExp expGenerals("([A-Za-z0-9_]\\w+)\\s(\\w+)");
        QRegExp expSkills("\\-(\\w+)(\\[(\\w+)\\])?");

        QString s = file.readLine();
        s = s.trimmed();
        if (s.isEmpty())
            continue;

        if (expGenerals.exactMatch(s)) {
            generals << expGenerals.capturedTexts().at(1);
            kingdoms << expGenerals.capturedTexts().at(2);
            skills << QMap<QString, QString>();
        }
        else if (expSkills.exactMatch(s)) {
            QString skill_name = expSkills.capturedTexts().at(1);
            QString original_owner = expSkills.capturedTexts().at(3);
            skills.last().insert(skill_name, original_owner);
        }
        else {
            file.close();
            return false;
        }
    }

    file.close();

    for (int i = 0; i < generals.length(); ++i) {
        General *general = new General(generals.at(i), kingdoms.at(i), this);
        foreach (QString skill_name, skills.at(i).keys())
            general->insertSkill(skill_name, skills.at(i)[skill_name]);
    }

    return true;
}

General::General(const QString &name, const QString &kingdom, Package *package) : kingdom(kingdom) {
    setObjectName(name);
    setParent(package);
}

const QString &General::getKingdom() const{
    return kingdom;
}

QStringList General::getSkills() const{
    return skills + other_owner_skills.keys();
}

void General::insertSkill(const QString &name, const QString &original_owner) {
    if (original_owner.isEmpty())
        skills << name;
    else
        other_owner_skills.insert(name, original_owner);
}
QString General::getSkillOwner(const QString &skill) const{
    if (skills.contains(skill))
        return objectName();
    else
        return other_owner_skills.value(skill, "");
}