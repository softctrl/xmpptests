#-------------------------------------------------
#
# Project created by QtCreator 2016-08-08T15:34:06
#
#-------------------------------------------------

QT       += core
QT       += network xml

QT       -= gui

TARGET = XmppTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app



SOURCES += main.cpp \
    sc_xmpp_client_boot.cpp \
    sc_xmpp_thread_boot.cpp

HEADERS += \
    sc_xmpp_client_boot.h \
    sc_xmpp_thread_boot.h

DISTFILES += \
    users.csv

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qxmpp/Release/src/release/ -lqxmpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qxmpp/Release/src/debug/ -lqxmpp
else:unix: LIBS += -L$$PWD/../qxmpp/Release/src/ -lqxmpp

INCLUDEPATH += $$PWD/../qxmpp/Release/src
DEPENDPATH += $$PWD/../qxmpp/Release/src
