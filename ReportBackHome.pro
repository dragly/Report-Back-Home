#-------------------------------------------------
#
# Project created by QtCreator 2010-08-20T10:58:27
#
#-------------------------------------------------

QT       += core

TARGET = ReportBackHome
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    reportbackhome.cpp
symbian {
TARGET.CAPABILITY = ReadUserData \
    WriteUserData \
    ReadDeviceData \
    WriteDeviceData
}

HEADERS += \
    reportbackhome.h

CONFIG += mobility
MOBILITY = messaging \
    location
