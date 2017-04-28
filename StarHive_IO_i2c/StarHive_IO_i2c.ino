#include "defs.h"
//#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(process_data);
  Serial.begin(9600);
}

void loop() {
  if(data_rcv==true)
  {
    if(command_buffer[0]==START_BYTE && command_buffer[4]==END_BYTE)
    {
      switch(command_buffer[1])
      {
        case CONFIG_IO_BYTE:
          pinMode(command_buffer[2],command_buffer[3]);
        break;
        case COMMAND_IO:
          digitalWrite(command_buffer[2],command_buffer[3]);
        break;
        case COMMAND_ANALOG:
          analogWrite(command_buffer[2],command_buffer[3]);
        break;
        
        case REQUEST_IO:
          io_state=digitalRead(command_buffer[2]);
          data_req=true;
          io_req=true;
        break;
        case REQUEST_ANALOG:
          analogval=analogRead(byte(A0)+byte(command_buffer[2]));
          data_req=true;
          analog_req=true;
        break;
        
        
      }
    }
    data_rcv=false;
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  if(data_req==true)
  {
    if(io_req==true)
    {
      Wire.write(io_state);
      io_req=false;
    }
    if(analog_req==true)
    {
      
      Wire.write((uint8_t)((analogval>>8) & 0xFF));
      Wire.write((uint8_t)(analogval & 0xFF));
      analog_req=false;
    }
    
    data_req=false;
  }
}

void process_data(int numbytes)
{
  int i=0;
  for(i=0;i<numbytes;i++)
  {
    command_buffer[i] = Wire.read(); // receive byte as a character
    //Serial.print(c,HEX);         // print the character
  }
  data_rcv=true;
  //Serial.println();
}

