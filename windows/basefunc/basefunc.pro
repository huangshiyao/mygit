TARGET = basefunc
TEMPLATE = lib
CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

SOURCES += \
        datetime.c \
        file.c \
        list.c

HEADERS += \
    basefunc.h
