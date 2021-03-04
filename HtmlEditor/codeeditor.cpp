#include "codeeditor.h"
#include <QPalette>
#include <windows.h>
#include <winuser.h>

CodeEditor::CodeEditor()
{
    QPalette pal;
    pal.setColor(QPalette::Text, Qt::white);
    pal.setColor(QPalette::Base, QRgb(0x5a5a5a));
    //this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setLineWrapMode(LineWrapMode::NoWrap);
}

void CodeEditor::wheelEvent(QWheelEvent *event)
{

    if(GetAsyncKeyState(VK_LCONTROL) & 0x81)
    {
        QFont f = this->font();
        int size = f.pointSize();
        size += event->angleDelta().y()/25;
        if(size>5)
            f.setPointSize(size);
        this->setFont(f);
    }
}
