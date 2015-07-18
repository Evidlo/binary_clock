#Evan Widloski - 2015-07-18
#Binary Clock Programmer - Sets time of RTC module on binary clock

#include <USI_TWI_Master.h>
#include <TinyWireM.h>

#define DS3231 0x68

#define DS 1
#define STCP2 2
#define SHCP2 3
#define STCP1 5
#define SHCP1 8

void setup() {
  int second = 0;
  int minute = 14;
  int hour = 4;
  int dayOfWeek = 0;
  int dayOfMonth = 18;
  int month = 7;
  int year = 15; 
  TinyWireM.begin();
  TinyWireM.beginTransmission(0x68);
  TinyWireM.write(0);
  TinyWireM.write(((second/10)<<4) + second%10);
  TinyWireM.write(((minute/10)<<4) + minute%10);
  TinyWireM.write((1<<6)+ ((hour/12)<<5) + ((hour/10)<<4) + hour%10);
  TinyWireM.write(1);
  TinyWireM.write(((dayOfMonth/10)<<4) + dayOfMonth%10);
  TinyWireM.write(((month/10)<<4) + month%10);
  TinyWireM.write(((year/10)<<4) + year%10);
  TinyWireM.endTransmission();


}

void loop(){

}
