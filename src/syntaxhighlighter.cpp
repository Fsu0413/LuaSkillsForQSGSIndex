#include "syntaxhighlighter.h"

LuaSyntaxHighlighter::LuaSyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    QStringList keywordPatterns;
    keywordPatterns << "_G" << "_VERSION" << "assert" << "collectgarbage"
                    << "dofile" << "error" << "getmetatable" << "ipairs"
                    << "load" << "loadfile" << "next" << "pairs"
                    << "pcall" << "print" << "rawequal" << "rawget"
                    << "rawlen" << "rawset" << "require" << "select"
                    << "setmetatable" << "tonumber" << "tostring" << "type"
                    << "xpcall";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }


    classFormat.setForeground(Qt::blue);
    QStringList classPatterns;
    classPatterns << "bit32" << "coroutine" << "debug" << "file"
                  << "io" << "math" << "os" << "package"
                  << "string" << "table"
                  << "and" << "break" << "do" << "else"
                  << "elseif" << "end" << "false" << "for"
                  << "function" << "goto" << "if" << "in"
                  << "local" << "nil" << "not" << "or"
                  << "repeat" << "return" << "then" << "true"
                  << "until" << "while"
                  << "sgs" << "self";
    foreach (const QString &pattern, classPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = classFormat;
        highlightingRules.append(rule);
    }

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("--[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("\".*\"");
    rule.pattern.setMinimal(true);
    rule.format = quotationFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\'.*\'");
    rule.pattern.setMinimal(true);
    highlightingRules.append(rule);

}

void LuaSyntaxHighlighter::highlightBlock(const QString &text) {
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            if (canHighlight(text, index, length))
                setFormat(index, length, rule.format);

            index = expression.indexIn(text, index + length);
        }
    }
}

bool LuaSyntaxHighlighter::canHighlight(const QString &str, int index, int length) {
    QRegExp exp1("\\w");
    if (exp1.exactMatch(QString(str.at(index - 1))))
        return false;

    if (index + length >= str.length())
        return true;

    QRegExp exp2("\\w");
    if (exp2.exactMatch(QString(str.at(index + length))))
        return false;

    return true;
}
