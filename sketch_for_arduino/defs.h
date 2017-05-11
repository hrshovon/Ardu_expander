#ifndef _DEFS_H_
#define _DEFS_H_
#include <Wire.h>


#define ADDRESS 0x08
#define BUFFER_LENGTH 5
//command from esp
//buffer
#define START_BYTE 0xE1
#define END_BYTE 0xAA
#define TERM_BYTE 0xFD

//commandset
//config
#define CONFIG_IO_BYTE 0xE2
#define CONFIG_IO_INTERRUPT 0xE7
//IO commands
#define COMMAND_IO 0xE3
#define COMMAND_ANALOG 0xE4 
#define REQUEST_IO 0xE5
#define REQUEST_ANALOG 0xE6

byte command_buffer[10];
byte io_state=0;
int analogval=0;
bool data_rcv=false;
bool data_req=false;
bool io_req=false;
bool analog_req=false;
#endif

