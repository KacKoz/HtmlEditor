#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QColor>
#include <QTextCursor>
#include <QSyntaxHighlighter>
#include <QPlainTextEdit>
#include <QVector>
#include <map>

#include "Configuration.h"



class syntaxHighlighter : QSyntaxHighlighter
{
public:
    syntaxHighlighter(QPlainTextEdit*);

    void highlightBlock( const QString&);
    void setConfig(const std::shared_ptr<config>& conf);



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
        comment,
        incorrectValue
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



   /* struct
    {
      QColor tagColor = Qt::yellow;
      QColor stringColor = Qt::red;
      QColor attributeColor = Qt::green;
      QColor normalColor = Qt::white;
      QColor numberColor =  Qt::cyan;
      QColor commentColor =  Qt::gray;
      QTextCharFormat incorrect;
    } colors;*/

    std::map<QString, QColor> colors;
    QTextCharFormat incorrect;

   // QVector<QRegularExpression> patterns;


};

#endif // SYNTAXHIGHLIGHTER_H
