#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class LuaSyntaxHighlighter : public QSyntaxHighlighter {
public:
    LuaSyntaxHighlighter(QTextDocument *parent = NULL);

protected:
    virtual void highlightBlock(const QString &text);

private:
    struct HighlightingRule {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat quotationFormat;

    static bool canHighlight(const QString &str, int index, int length);
};


#endif // SYNTAXHIGHLIGHTER_H
