#include "Arduino.h"
#include "ardu_expander.h"
#include "Wire.h"


#define START_BYTE 0xE1
#define END_BYTE 0xAA
#define CONFIG_IO_BYTE 0xE2
#define CONFIG_IO_INTERRUPT 0xE7
#define COMMAND_IO 0xE3
#define COMMAND_ANALOG 0xE4 
#define REQUEST_IO 0xE5
#define REQUEST_ANALOG 0xE6


Ardu_expander::Ardu_expander(uint8_t addr)
{
  #if defined(ESP8266)
   Wire.begin(SDA_pin,SCL_pin);        // join i2c bus (address optional for master)
  #else
   Wire.begin();
  #endif 
  ADDRESS=addr; 
}

void Ardu_expander::STpinMode(uint8_t pin,uint8_t value)
{
  Wire.beginTransmission(ADDRESS);
  Wire.write(START_BYTE);
  Wire.write(CONFIG_IO_BYTE);
  Wire.write(byte(pin));
  Wire.write(byte(value));
  Wire.write(END_BYTE);
  Wire.endTransmission();
  //delay(10);
}

void Ardu_expander::STdigitalWrite(uint8_t pin,uint8_t value)
{
  Wire.beginTransmission(ADDRESS);
  Wire.write(START_BYTE);
  Wire.write(COMMAND_IO);
  Wire.write(byte(pin));
  Wire.write(byte(value));
  Wire.write(END_BYTE);
  Wire.endTransmission();
}

void Ardu_expander::STdigitalWrite_force(uint8_t pin,uint8_t value)
{
  STpinMode(pin,OUTPUT);
  Wire.beginTransmission(ADDRESS);
  Wire.write(START_BYTE);
  Wire.write(COMMAND_IO);
  Wire.write(byte(pin));
  Wire.write(byte(value));
  Wire.write(END_BYTE);
  Wire.endTransmission();
}


uint8_t Ardu_expander::STdigitalRead(uint8_t pin)
{
  Wire.beginTransmission(ADDRESS);
  Wire.write(START_BYTE);
  Wire.write(REQUEST_IO);
  Wire.write(byte(pin));
  Wire.write(byte(1));
  Wire.write(END_BYTE);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS,(byte)1);
  
  return Wire.read();
}

int Ardu_expander::STanalogRead(uint8_t pin)
{
  int msb;
  int lsb;
  
  Wire.beginTransmission(ADDRESS);
  Wire.write(START_BYTE);
  Wire.write(REQUEST_ANALOG);
  Wire.write(byte(pin));
  Wire.write(byte(1));
  Wire.write(END_BYTE);
  Wire.endTransmission();
  delayMicroseconds(500);
  Wire.requestFrom(ADDRESS,(byte)2);
  msb=Wire.read();
  lsb=Wire.read();
  return ((msb*256)+lsb);
}
