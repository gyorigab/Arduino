QT -= core
QT -= gui

CONFIG -= c++11

TARGET = testing
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
        ../../radio.cpp\
        ../../trace.cpp\
        ../../../controler/controler.cpp\
        ../../../quadcopter/quadcopter.cpp\
        ../../../controler/joystick.cpp\
        ../../../controler/radio.cpp\
        unittests.cpp

HEADERS += \
    unittests.h \
    ../../bytebuffer.h \
    ../../packet.h \
    ../../hashmap.h\
    ../../message.h \
    ../../radio.h\
    ../../trace.h\
    ../../../quadcopter/quadcopter.h\
    ../../../controler/controler.h\
    ../../../controler/joystick.h\
    bytebuffertest.h \
    packettest.h \
    hashmaptest.h \
    messagetest.h
