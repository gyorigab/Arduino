  #include <radio.h>
#include <quadcopter.h>

#include <RF24_config.h>
#include <SPI.h>

Quadcopter q;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  q.init();
}

void loop() 
{
  // put your main code here, to run repeatedly: 
  /*ByteBuffer stream = radio.read();*/
  ByteBuffer stream = q.go();
  Serial.println(stream.cptr());
  delay(1000);
}
