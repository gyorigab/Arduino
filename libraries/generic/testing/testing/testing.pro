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
        ../../messageext.cpp\
        ../../radio.cpp\
        ../../trace.cpp\
        ../../utils.cpp\
        ../../timer.cpp\
        ../../angle.cpp\
        ../../plot.cpp\
        ../../../quadcopter/quadcopter.cpp\
        ../../../quadcopter/controlerdata.cpp\
        ../../../quadcopter/motor.cpp\
        ../../../quadcopter/motorcontrol.cpp\
        ../../../quadcopter/gyroscope.cpp\
        ../../../quadcopter/pid.cpp\
        ../../../controler/controler.cpp\
        ../../../controler/controlermessage.cpp\
        ../../../controler/joystick.cpp\
        unittests.cpp

HEADERS += \
    unittests.h \
    ../../bytebuffer.h \
    ../../packet.h \
    ../../hashmap.h\
    ../../message.h \
    ../../messageext.h\
    ../../radio.h\
    ../../trace.h\
    ../../utils.h\
    ../../timer.h\
    ../../angle.h\
    ../../plot.h\
    ../../../quadcopter/quadcopter.h\
    ../../../quadcopter/controlerdata.h\
    ../../../quadcopter/motor.h\
    ../../../quadcopter/motorcontrol.h\
    ../../../quadcopter/gyroscope.h\
     ../../../quadcopter/pid.h\
    ../../../controler/controler.h\
    ../../../controler/controlermessage.h\
    ../../../controler/joystick.h\
    bytebuffertest.h \
    packettest.h \
    hashmaptest.h \
    messagetest.h
