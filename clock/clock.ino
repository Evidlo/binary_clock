//Evan Widloski - 2015-07-18
//Binary clock - Retrieves date from RTC and displays on a 4 digit binary display

#include <USI_TWI_Master.h>
#include <TinyWireM.h>

#define DS3231 0x68
#define DS 1     //data in
#define STCP2 2  //storage register 2 clock
#define SHCP2 3  //shift register 2 clock
#define STCP1 5  //storage register 1 clock
#define SHCP1 8  //shift register 1 clock

void setup() {
  //initialize IO
  TinyWireM.begin();
  pinMode(DS,OUTPUT);
  pinMode(STCP1,OUTPUT);
  pinMode(SHCP1,OUTPUT);
  pinMode(STCP2,OUTPUT);
  pinMode(SHCP2,OUTPUT);
  digitalWrite(SHCP1,LOW);
  digitalWrite(STCP1,LOW);
  digitalWrite(SHCP2,LOW);
  digitalWrite(STCP2,LOW);
  clear();
}

//clear the shift registers
void clear(){
  digitalWrite(DS,LOW);
  for(int i=0;i<16;i++){
  digitalWrite(SHCP1,LOW);
  digitalWrite(SHCP2,LOW);
  delay(1);
  digitalWrite(SHCP1,HIGH);
  digitalWrite(SHCP2,HIGH);
  delay(1);
  }
  digitalWrite(STCP1,LOW);
  digitalWrite(STCP2,LOW);
  delay(1);
  digitalWrite(STCP1,HIGH);
  digitalWrite(STCP2,HIGH);
}


//clock the storage registers
void display(){
  digitalWrite(STCP1,LOW);
  digitalWrite(STCP2,LOW);
  delay(1);
  digitalWrite(STCP1,HIGH);
  digitalWrite(STCP2,HIGH);
  delay(1);
  }
  
//clock the shift registers
void clock(){
  digitalWrite(SHCP1,LOW);
  delay(1);
  digitalWrite(SHCP1,HIGH);

  digitalWrite(SHCP2,LOW);
  delay(1);
  digitalWrite(SHCP2,HIGH);
}
  
//shift in 8 bits
void shift_byte(char c){
  for(int i=7;i>=0;i--){
    digitalWrite(DS,(c>>i)%2);
    clock();
  }
}

//calculate DST
//ripped from http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date
int DST(int month,int dow, int day){
    //January, february, and december are out.
    if (month < 3 || month > 11) { return false; }
    //April to October are in
    if (month > 3 && month < 11) { return true; }
    int previousSunday = day - dow;
    //In march, we are DST if our previous sunday was on or after the 8th.
    if (month == 3) { return previousSunday >= 8; }
    //In november we must be before the first sunday to be dst.
    //That means the previous sunday must be before the 1st.
    return previousSunday <= 0;
}

//convert bcd to decimal
int toDec(char c){
  return (c/16)*10 + c%16;
}

void loop() {
  TinyWireM.beginTransmission(DS3231);
  TinyWireM.write(0);
  TinyWireM.endTransmission();
  TinyWireM.requestFrom(DS3231,6);
  
  //read time from RTC module
  int seconds = toDec(TinyWireM.read()); //second
  int minutes = toDec(TinyWireM.read()); //minute
  int hours = toDec(TinyWireM.read() % 32);  //cut off 12/24h bit before processing hours
  int dow = toDec(TinyWireM.read()); //day of week
  int day = toDec(TinyWireM.read()); //day of month
  int month = toDec(TinyWireM.read() % 32); //cut off century bit before processing month

  hours += DST(month,dow,day); //calculate DST
  
  //write time to display in base 10
  shift_byte(((hours/10)<<4) + (hours%10));
  shift_byte(((minutes/10)<<4) + (minutes%10));
  display(); 

  delay(100);

}
