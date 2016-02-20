#include <InvertedTM1638.h>
#include <TM1638.h>
#include <TM1640.h>
#include <TM16XX.h>
#include <TM16XXFonts.h>

//Arduino 1.0+ Only

// Read the Real Time Clock (RTC) and write to the Serial Port
// Matt Simmons  04/05/2012
#include "Wire.h"
#define DS1307_ADDRESS 0x68

void setup(){
  Wire.begin();
  Serial.begin(57600);
}

void loop(){
  printDate();
  delay(1000);
}

byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

void printDate(){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);

  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int second = bcdToDec(Wire.read());
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = bcdToDec(Wire.read());

  // Send to Serial Port
  Serial.print("H");
  Serial.print(",");
  Serial.print(month);
  Serial.print("/");
  Serial.print(monthDay);
  Serial.print("/");
  Serial.print(year);
  Serial.print(",");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second);
  Serial.print(",");
  Serial.println("");
}
