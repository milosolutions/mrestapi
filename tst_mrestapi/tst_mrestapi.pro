QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \ 
    tst_restrequest.cpp \
    restapiclient.cpp \
    weatherbycitynamerequest.cpp

HEADERS += \
    restapiclient.h \
    weatherbycitynamerequest.h

include(../mrestapi.pri)
