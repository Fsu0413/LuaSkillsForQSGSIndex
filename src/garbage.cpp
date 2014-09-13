#include "garbage.h"

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

Package::Package(const QString &name) {
    setObjectName(name);
    setParent(Garbage::getInstance());
}

General::General(const QString &name, const QString &kingdom, Package *package) : kingdom(kingdom) {
    setObjectName(name);
    setParent(package);
}

const QString &General::getKingdom() const{
    return kingdom;
}

const QStringList &General::getSkills() const{
    return skills;
}

void General::insertSkill(const QString &name) {
    skills << name;
}
