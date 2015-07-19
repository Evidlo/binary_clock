//Evan Widloski - 2015-07-18
//Binary Clock Programmer - Sets time of RTC module on binary clock

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
  int minute = 27;
  int hour = 7;
  int dayOfWeek = 0;
  int dayOfMonth = 18;
  int month = 7;
  int year = 15; 
  TinyWireM.begin();
  TinyWireM.beginTransmission(0x68);
  TinyWireM.write(0);
  TinyWireM.write(((second/10)<<4) + second%10);                                     //write seconds
  TinyWireM.write(((minute/10)<<4) + minute%10);                                     //write minutes
  TinyWireM.write((1<<6) + (1<<5) + ((hour/12)<<5) + ((hour/10)<<4) + hour%10);      //set to 12h mode, set pm, and write hour;
  TinyWireM.write(1);                                                                //write arbitrary day of week
  TinyWireM.write(((dayOfMonth/10)<<4) + dayOfMonth%10);                             //write day of month
  TinyWireM.write(((month/10)<<4) + month%10);                                       //write month
  TinyWireM.write(((year/10)<<4) + year%10);                                         //write 2 digit year
  TinyWireM.endTransmission();


}

void loop(){

}
