#include "skill_translator.h"

//QHash<QString, QString> SkillTranslator::translations;

QString SkillTranslator::translate(const QString &from) {
    return translations.value(from, "N/A");
}

void SkillTranslator::insertTranslationPair(const QString &from, const QString &to) {
    translations.insert(from, to);
}
