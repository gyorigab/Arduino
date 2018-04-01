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
  /*i++;
  char digit[10];
  snprintf(digit,sizeof(digit),"%d",i);
  ByteBuffer test((uint8_t *)&digit, sizeof(digit));
  radio.write(test);*/
  
  /*uint8_t input[3] = {0x41, 0x42, 0x43};
  ByteBuffer test(input, 3);
  Trace::print(test.cptr());*/
  
  //Trace::print(data.upper);
  delay(1000);
}
