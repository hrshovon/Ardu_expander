#include <ardu_expander.h>

#define ADDRESS 0x08 //change it according to your need

Ardu_expander ardu_exp(ADDRESS);

void setup()
{
	ardu_exp.STpinMode(8,OUTPUT);
}

void loop()
{
	ardu_exp.STdigitalWrite(8,HIGH);
	delay(1000);
	ardu_exp.STdigitalWrite(8,LOW);
	delay(1000);
}
