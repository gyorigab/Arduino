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
    
  Trace::enableCallStack(true);
  Trace::enableTrace(true);
  Trace::verbosity(Trace::DEBUG);
}

void loop() 
{
  ByteBuffer stream = q.go();
  delay(500);
}
