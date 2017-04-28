/*
	Ardu_expander, a method to use another arduino as port expander
*/
#ifndef Ardu_expander_h
#define Ardu_expander_h
#define SDA_pin 12
#define SCL_pin 14

#include "Arduino.h"

class Ardu_expander
{
	public:
		Ardu_expander(uint8_t addr);
		void STpinMode(uint8_t pin,uint8_t value);
		void STdigitalWrite(uint8_t pin,uint8_t value);
		void STdigitalWrite_force(uint8_t pin,uint8_t value);
		uint8_t STdigitalRead(uint8_t pin);
		int STanalogRead(uint8_t pin);
	private:
		uint8_t ADDRESS=0;
};
#endif