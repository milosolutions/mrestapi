QT += core network
CONFIG += c++11
DEFINES *= QT_USE_QSTRINGBUILDER

OTHER_FILES += $$PWD/README.md $$PWD/AUTHORS.md $$PWD/mrestapi.doxyfile

HEADERS += \
    $$PWD/restCommunicationCore/mconfig.h \
    $$PWD/restCommunicationCore/mrestrequest.h \
    $$PWD/restCommunicationCore/mrestrequestqueue.h \
    $$PWD/restCommunicationCore/mrestrequestmanager.h \
    $$PWD/restCommunicationCore/mrestrequestptr.h \
    $$PWD/restCommunicationCore/mrestrequestconfig.h

SOURCES += \
    $$PWD/restCommunicationCore/mconfig.cpp \
    $$PWD/restCommunicationCore/mrestrequest.cpp \
    $$PWD/restCommunicationCore/mrestrequestqueue.cpp \
    $$PWD/restCommunicationCore/mrestrequestmanager.cpp \
    $$PWD/restCommunicationCore/mrestrequestconfig.cpp

INCLUDEPATH += $$PWD/restCommunicationCore/
#DISTFILES += \
#    $$PWD/AUTHORS.md

production-server {
    DEFINES += USE_PRODUCTION_SERVER
}
