#ifndef _SKILL_TRANSLATOR_H_
#define _SKILL_TRANSLATOR_H_

#include <QString>
#include <QHash>


namespace SkillTranslator {
    static QString translate(const QString &from);
    static void insertTranslationPair(const QString &from, const QString &to);
    
    static QHash<QString, QString> translations;
};


#endif
