# Ardu_expander
A library along with an arduino sketch to use an Arduino board as a port expander.

Usage :
Everything is pretty much the same as using pinMode/digitalWrite/digitalRead functions in standard arduino.You just add an ST before that.
For example:
you are initiating the library this way

#define ADDRESS 0x08
Ardu_expander ard_IO(ADDRESS);

Then when you want to set pinMode: 
ardIO.STpinMode(10,OUTPUT);

same goes for analogRead etc.
Currently many functions are unavailable such as interrupts etc which would be added as soon as possible
