QT += core network
CONFIG += c++11
DEFINES *= QT_USE_QSTRINGBUILDER

OTHER_FILES += $$PWD/README.md $$PWD/AUTHORS.md $$PWD/mrestapi.doxyfile

HEADERS += \
    $$PWD/mrestrequest.h \
    $$PWD/mrestrequestqueue.h \
    $$PWD/mrestrequestmanager.h \
    $$PWD/mrestrequestptr.h

SOURCES += \
    $$PWD/mrestrequest.cpp \
    $$PWD/mrestrequestqueue.cpp \
    $$PWD/mrestrequestmanager.cpp

INCLUDEPATH += $$PWD
#DISTFILES += \
#    $$PWD/AUTHORS.md

production-server {
    DEFINES += USE_PRODUCTION_SERVER
}
