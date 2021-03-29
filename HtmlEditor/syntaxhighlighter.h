#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QColor>
#include <QTextCursor>
#include <QSyntaxHighlighter>
#include <QPlainTextEdit>
#include <QVector>
#include <QRegularExpression>



class syntaxHighlighter : QSyntaxHighlighter
{
public:
    syntaxHighlighter(QPlainTextEdit* parent);

    void highlightBlock( const QString& text);




private:
    enum lineStates
    {
        NORMAL = 0,
        STRING = 1,
        ATTRIBUTE = 2,
        VALUE = 3,
        ASSIGN = 4,
        COMMENT = 5,
        SCRIPT = 6
    }; ///TODO: script

    enum class currentState
    {
        beggining,
        attribute,
        value,
        assign,
        string,
        tagName,
        number,
        comment
    };

   /* enum pttrn_idx
    {
        openingBr = 0,
        tagName = 1,
        attribute = 2,
        value = 3,
        literal = 4,
        closingBr = 5
    };*/



    struct
    {
      QColor tagColor = Qt::yellow;
      QColor stringColor = Qt::red;
      QColor attributeColor = Qt::green;
      QColor normalColor = Qt::white;
      QColor numberColor =  Qt::cyan;
      QColor commentColor =  Qt::gray;
    } colors;

   // QVector<QRegularExpression> patterns;

};

#endif // SYNTAXHIGHLIGHTER_H
