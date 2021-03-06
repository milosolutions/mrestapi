include(../mrestapi.pri)

exists(../../../tests/testConfig.pri) {
    include(../../../tests/testConfig.pri)
} else {
    warning("File testConfig.pri was not included")
}

QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \ 
    tst_mrestapi.cpp \
    restapiclient.cpp \
    weatherbycitynamerequest.cpp \
    testrequest.cpp

HEADERS += \
    restapiclient.h \
    weatherbycitynamerequest.h \
    testrequest.h

