#include <Arduino.h>

class test
{
public:
	 test(uint8_t m){a = m;}
	~test(){}
	 void go(){ Serial.println("test"); }
private:
	uint8_t a;
};
