#-------------------------------------------------
#
# Project created by QtCreator 2013-12-27T15:39:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtLedTest
TEMPLATE = app

QTPLUGIN += qledmatrix

SOURCES += main.cpp \
    graphics.cpp \
    font_data/*.c \
    font_info.cpp \
    ssd1306.cpp \
    mainwindow.cpp

HEADERS  += \
    graphics.h \
    font_info.h \
    font_data/*.h \
    ssd1306.h \
    mainwindow.h

FORMS    += \
    ssd1306.ui \
    mainwindow.ui

unix:!macx:!symbian: LIBS += -L$$PWD/../QLedMatrix/build/ -lqledmatrix

INCLUDEPATH += $$PWD/../QLedMatrix/
DEPENDPATH += $$PWD/../QLedMatrix/
