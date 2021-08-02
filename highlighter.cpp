#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent){
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\band\\b"), QStringLiteral("\\bas\\b"), QStringLiteral("\\bassert\\b"),
        QStringLiteral("\\bbreak\\b"), QStringLiteral("\\bclass\\b"), QStringLiteral("\\bcontinue\\b"),
        QStringLiteral("\\bdef\\b"), QStringLiteral("\\bdel\\b"), QStringLiteral("\\belif\\b"),
        QStringLiteral("\\belse\\b"), QStringLiteral("\\bexcept\\b"), QStringLiteral("\\bfinally\\b"),
        QStringLiteral("\\bfor\\b"), QStringLiteral("\\bfrom\\b"), QStringLiteral("\\bFalse\\b"),
        QStringLiteral("\\bglobal\\b"), QStringLiteral("\\bif\\b"), QStringLiteral("\\bimport\\b"),
        QStringLiteral("\\bin\\b"), QStringLiteral("\\bis\\b"), QStringLiteral("\\blambda\\b"),
        QStringLiteral("\\bnonlocal\\b"), QStringLiteral("\\bnot\\b"), QStringLiteral("\\bNone\\b"),
        QStringLiteral("\\breturn\\b"), QStringLiteral("\\btry\\b"), QStringLiteral("\\bTrue\\b"),
        QStringLiteral("\\bwhile\\b"), QStringLiteral("\\bwith\\b"), QStringLiteral("\\byield\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z_][A-Za-z0-9_]*\\(.*\\)"));
    rule.format = classFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression(QStringLiteral("#[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression(QStringLiteral("\'\'\'"));
    commentEndExpression = QRegularExpression(QStringLiteral("\'\'\'"));
}

void Highlighter::highlightBlock(const QString &text){
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
