QT -= core
QT -= gui

CONFIG -= c++11

TARGET = unittesting
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += GDEBUG

#INCLUDEPATH += /usr/share/arduino/hardware/arduino/avr/cores/arduino/
#INCLUDEPATH += /usr/avr/include/
#INCLUDEPATH += /usr/share/arduino/hardware/arduino/avr/variants/standard/

#INCLUDEPATH += /home/gabriel/Arduino/libraries/generic/

SOURCES += main.cpp \
        ../../message.cpp\
        ../../messageext.cpp\
        ../../trace.cpp\
        ../../utils.cpp\
        ../../angle.cpp\
        unittests.cpp

HEADERS += \
    unittests.h \
    ../../bytebuffer.h \
    ../../packet.h \
    ../../hashmap.h\
    ../../message.h \
    ../../messageext.h\
    ../../trace.h\
    ../../utils.h\
    ../../angle.h\
    bytebuffertest.h \
    packettest.h \
    hashmaptest.h \
    messagetest.h \
    messagetestext.h
