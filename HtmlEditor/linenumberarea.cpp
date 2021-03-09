#include "linenumberarea.h"


LineNumberArea::LineNumberArea(QWidget *parent) : QPlainTextEdit(parent)
{
    QSizePolicy sp;
    sp.setHorizontalPolicy(QSizePolicy::Fixed);
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    this->setSizePolicy(sp);
    this->setMaximumSize(20, 10000);
    QPalette pal;
    pal.setColor(QPalette::Text, Qt::green);
    pal.setColor(QPalette::Base, QRgb(0x5a5a5a));
    this->setPalette(pal);
    //this->setReadOnly(true);
    this->setTextInteractionFlags(Qt::NoTextInteraction);
    this->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    //this->appendPlainText("1\n");
    connect(this, &LineNumberArea::shouldChangeSize, this, &LineNumberArea::onShouldChangeSize);

}

void LineNumberArea::handleFontSize(int size)
{
    QFont f = this->font();
    f.setPointSize(size);
    this->setFont(f);

    emit shouldChangeSize();

}

void LineNumberArea::wheelEvent(QWheelEvent *event)
{

}

void LineNumberArea::onShouldChangeSize()
{
    QFont f = this->font();
    QFontMetrics fm(f);
    this->setMaximumWidth(fm.horizontalAdvance(QString::fromStdString(std::to_string(_lines))) + 10);
}

void LineNumberArea::onBlockCountVector(std::vector<int>* v)
{
    int c = v->size();
    _lines = c;
    _lineNumbers = "";
    for(int i=0; i<c; i++)
    {
        qDebug() << "Line: " << i << " count: " << v->at(i);
        _lineNumbers.append(QString::fromStdString(std::to_string(i + 1)));
        for(int j = 0; j < v->at(i); j++)
        {
            _lineNumbers.append("\n");
        }
    }

   this->setPlainText(_lineNumbers);

   emit shouldChangeSize();
}
