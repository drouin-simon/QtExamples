#-------------------------------------------------
#
# Project created by QtCreator 2017-01-30T19:36:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = TestProportionalGlWidget
TEMPLATE = app


SOURCES += main.cpp\
        Widget.cpp \
    glWidget.cpp \
    AspectRatioWidget.cpp

HEADERS  += Widget.h \
    glWidget.h \
    AspectRatioWidget.h

FORMS    += Widget.ui
