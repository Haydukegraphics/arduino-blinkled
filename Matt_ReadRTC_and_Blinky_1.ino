// Print random DEC to the serial port with blinky light w/o delays
// MS 03/19/2011

#include "Wire.h"
#define DS1307_ADDRESS 0x68

// Global Variables
int ledState                = LOW;      // ledState used to set the LED
long previousLedMillis      = 0;        // will store last time LED was updated
long previousDataMillis     = 0;        // will store last time LED was updated
// long intervalLed         = 60;       // interval at which to blink Led (milliseconds)
long intervalData           = 5000;     // interval at which to send data (milliseconds)
const int sensorPin         = 0 ;       // Input for freq of blinky
const int minDuration       = 60;       // min Led blinky rate
const int maxDuration       = 1000;     // max Led blinky rate

void setup() {
  Serial.begin(57600);   // open a serial port
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
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
  
  Serial.print('H');              // any START OF STRING identifier
  Serial.print(',');              // string separator
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
  Serial.println(second);
  Serial.print(',');              // string separator
  Serial.println("");             // finish with \r\n
}

void loop () {
  // Get the time
  unsigned long currentMillis = millis();
  // Blink Random LED because who doesn't like blinky lights. Pick a Led pin
  int RandomLed = random(10, 14);
  // See if its time to update
  int rate = analogRead(sensorPin);   // read the analog pin for a value
  rate = map(rate, 10, 1000, minDuration, maxDuration);
  if(currentMillis - previousLedMillis > rate) {
    // Save the last time we blinked the LED
    previousLedMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) ledState = HIGH;
      else ledState = LOW;
      // set the LED with the ledState of the variable:
      digitalWrite(RandomLed, ledState);
  }
 
  // Send at timed intervals (intervalData)
  if(currentMillis - previousDataMillis > intervalData) {
    // save the last time we sent data
    previousDataMillis = currentMillis;
    // Send the Data
    printDate();
  }
}

