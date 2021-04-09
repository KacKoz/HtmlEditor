QT       += core gui 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    autocomplete.cpp \
    browserview.cpp \
    button.cpp \
    codeeditor.cpp \
    codeeditorarea.cpp \
    dirtree.cpp \
    linenumberarea.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp \
    syntaxhighlighter.cpp \
    tagslist.cpp \
    tagstree.cpp \
    tagsuggestion.cpp
 

HEADERS += \
    autocomplete.h \
    browserview.h \
    button.h \
    codeeditor.h \
    codeeditorarea.h \
    dirtree.h \
    linenumberarea.h \
    mainwindow.h \
    parser.h \
    syntaxhighlighter.h \
    tagslist.h \
    tagstree.h \
    tagsuggestion.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dsffsd/dsfsd.txt \
    dsffsd/papapa/tatatat.txt
