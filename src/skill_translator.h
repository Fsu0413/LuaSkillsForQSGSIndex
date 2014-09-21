#ifndef _SKILL_TRANSLATOR_H_
#define _SKILL_TRANSLATOR_H_

#include <QString>
#include <QHash>


namespace SkillTranslator {
    QString translate(const QString &from);
    void insertTranslationPair(const QString &from, const QString &to);
};


#endif
