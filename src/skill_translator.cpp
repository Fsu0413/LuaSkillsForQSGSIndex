#include "skill_translator.h"

QHash<QString, QString> translations;

QString SkillTranslator::translate(const QString &from) {
    return translations.value(from, from);
}

void SkillTranslator::insertTranslationPair(const QString &from, const QString &to) {
    translations.insert(from, to);
}
