#ifndef _SKILL_TRANSLATOR_H_
#define _SKILL_TRANSLATOR_H_

#include <QString>
#include <QHash>


class SkillTranslator {
public:
    static QString translate(const QString &from);
    static void insertTranslationPair(const QString &from, const QString &to);
    
private:
    SkillTranslator();
    SkillTranslator(const SkillTranslator &);
    
private:
    static QHash<QString, QString> translations;
};


#endif
