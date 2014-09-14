#ifndef _GARBAGE_H_
#define _GARBAGE_H_

#include <QString>
#include <QStringList>
#include <QMap>
#include <QFile>

class Package;
class General;

class Garbage : public QObject {
    Q_OBJECT

public:
    static Garbage *getInstance();
    static void destroyInstancce();

    inline QList<const Package *> getPackages() const { return findChildren<const Package *>(QString(), Qt::FindDirectChildrenOnly); }
    inline QList<const General *> getGenerals() const { return findChildren<const General *>(QString(), Qt::FindChildrenRecursively); }

    inline const Package *getPackage(const QString &name) const { return findChild<const Package *>(name, Qt::FindDirectChildrenOnly); }
    inline const General *getGeneral(const QString &name) const { return findChild<const General *>(name, Qt::FindChildrenRecursively); }

private:
    Garbage();
    Garbage(const Garbage &);

    static Garbage *instance;
};

class Package : public QObject {
    Q_OBJECT

public:
    explicit Package(const QString &name, Garbage *garbage);

private:
    Package(const Package &);

    bool exportGenerals(QFile &file);

};

class General : public QObject {
    Q_OBJECT

public:
    General(const QString &name, const QString &kingdom, Package *package);

    const QString &getKingdom() const;
    void insertSkill(const QString &name, const QString &original_owner = QString());
    QStringList getSkills() const;
    QString getSkillOwner(const QString &skill) const;

    QString getPackage() const;

private:
    General(const General &);

private:
    QStringList skills;
    QString kingdom;
    QMap<QString, QString> other_owner_skills;
};

#endif