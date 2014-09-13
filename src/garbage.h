#ifndef _GARBAGE_H_
#define _GARBAGE_H_

#include <QString>
#include <QStringList>

class Garbage : public QObject{
    Q_OBJECT

public:
    static Garbage *getInstance();
    static void destroyInstancce();



private:
    Garbage();
    Garbage(const Garbage &);

    static Garbage *instance;
};

class Package : public QObject{
    Q_OBJECT

public:
    explicit Package(const QString &name);

private:
    Package(const Package &);

};

class General : public QObject{
    Q_OBJECT

public:
    General(const QString &name, const QString &kingdom, Package *package);

    const QString &getKingdom() const;
    void insertSkill(const QString &name);
    const QStringList &getSkills() const;

private:
    General(const General &);

private:
    QStringList skills;
    QString kingdom;
};

#endif