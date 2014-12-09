#-------------------------------------------------
#
# Project created by QtCreator 2014-12-06T23:54:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlockCipherProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    intropage.cpp \
    getpassword.cpp

HEADERS  += mainwindow.h \
    intropage.h \
    getpassword.h

FORMS    += \
    IntroPage.ui \
    Password.ui
