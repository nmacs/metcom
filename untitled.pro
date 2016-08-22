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
    zcommlog.cpp \
    connect.cpp \
    firmwareupgrade.cpp \
    progress.cpp \
    zcommlogdialog.cpp \
    passwordchangedlg.cpp \
    zpasswordchange.cpp \
    zsettingsgui.cpp

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
    zcommlog.h \
    connect.h \
    firmwareupgrade.h \
    progress.h \
    zcommlogdialog.h \
    passwordchangedlg.h \
    zpasswordchange.h \
    zsettingsgui.h

FORMS    += mainwindow.ui \
    connect.ui \
    fwupgrade_2.ui \
    firmwareupgrade.ui \
    progress.ui \
    zcommlogdialog.ui \
    passwordchangedlg.ui

TRANSLATIONS += app_en.ts
TRANSLATIONS += app_ru.ts

DISTFILES += \
    icon.png

