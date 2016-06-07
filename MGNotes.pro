#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T18:47:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OmniMG
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    skill_firearm_armor.cpp \
    calculator.cpp

HEADERS  += mainwindow.h \
    player.h \
    skill_firearm_armor.h \
    calculator.h

FORMS    += mainwindow.ui \
    calculator.ui

RESOURCES += \
    resources.qrc
RC_ICONS = mainicon.ico
