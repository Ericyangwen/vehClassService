QT -= gui
QT += network

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += debug_and_release

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = JDLine32.Service

SOURCES += \
        ctcpserver.cpp \
        main.cpp \
        Utils.cpp \
        vehtypeservice.cpp \
        vehtypemodelapp.cpp \
        vehtypemodelworker.cpp \
        model/dll32lidarmodel.cpp

HEADERS += \
    GQueue.h \
    common.h \
    ctcpserver.h \
    Utils.h \
    vehtypeservice.h \
    vehtypemodelapp.h \
    vehtypemodelworker.h \
    model/dll32lidarmodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(debug, debug|release){
    DESTDIR = ../JDLine32.App/debug
}else{
    DESTDIR = ../JDLine32.App/release
}

# qtservice
include(./qtservice/src/qtservice.pri)

## 异常捕获
#LIBS += -lDbgHelp
