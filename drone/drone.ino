#include <Wire.h>
#include <Servo.h>

#include <radio.h>
#include <quadcopter.h>

#include <RF24_config.h>
#include <SPI.h>

Quadcopter q;
Trace t;

void setup() 
{
  t.init();
  q.init();
    
  Trace::enableCallStack(false);
  Trace::enableTrace(false);
  Trace::setVerbosity(DBG);
}

void loop() 
{
  ByteBuffer stream = q.go();
}
