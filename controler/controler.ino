#include <controler.h>
#include <radio.h>
#include <RF24_config.h>
#include <SPI.h>
#include <joystick.h>
#include <trace.h>

Controler c;
Trace t;

void setup() 
{
  t.init();
  c.init();
  
  Trace::enableCallStack(true);
  Trace::enableTrace(true);
  Trace::verbosity(Trace::DEBUG);
}

void loop() 
{ 
  c.go();
  delay(500);
}
