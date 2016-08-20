#-------------------------------------------------
#
# Project created by QtCreator 2016-06-16T14:24:12
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MetCOM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zchannel.cpp \
    zchanneldirectserial.cpp \
    zprotocol.cpp \
    zfirmwareupgrade.cpp \
    ipctrl.cpp \
    zreadsettings.cpp \
    zsettings.cpp \
    zsettingsview.cpp \
    zsettingstable.cpp \
    zwritesettings.cpp \
    zcommlog.cpp

HEADERS  += mainwindow.h \
    zchannel.h \
    zchanneldirectserial.h \
    zprotocol.h \
    zfirmwareupgrade.h \
    ipctrl.h \
    zreadsettings.h \
    zsettings.h \
    zsettingsview.h \
    zsettingstable.h \
    zwritesettings.h \
    zcommlog.h

FORMS    += mainwindow.ui \
    connection.ui \
    fwupgrade.ui

TRANSLATIONS += app_en.ts
TRANSLATIONS += app_ru.ts

