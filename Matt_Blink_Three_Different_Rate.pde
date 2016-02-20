/* Matt Blink Clock Segments
 
 Incerments the Chips driving an array of 7-Segment displays connected to digital pins. 
 (Code can run multiple pins at different rates at the same time.)
 
 The circuit:
 * LED attached from pin 13 to ground. Note: If wanted for testing, alreay on most Arduinos (LED on the board that's attached to pin 13)
 * 6 ea. 7-Segment Displays (or 3 Dual 7-Segmant Displays)
 * 6 ea. CMOS 4026B Chips
 * See Schematic for wireing instructions.
 
 Initial build 0.01: 02/15/2011:  Matt Simmons - This example code is in the public domain.
 Rev 0.02: 02/19/2011:  Fixed Reset Logic, typos in comments */

// Constants and Varaibles

// Constants
// set pin numbers:
const int led13Pin =  13;      // the number of the LED heardbeat pin
const int led12Pin =  12;      // the number of the LED seconds pin
const int led11Pin =  11;      // the number of the LED minutes pin
const int led10Pin =  10;      // the number of the LED hours pin

// Variables
// Load Initial States, 0 out counters, set intervals
int led13State = LOW;          // led13State used to set the LED 13
int led12State = LOW;          // led12State used to set the LED 12
int led11State = LOW;          // led11State used to set the LED 11
int led10State = LOW;          // led10State used to set the LED 10
long previous13Millis = 0;     // store last time 13LED was updated
long previous12Millis = 0;     // store last time 12LED was updated
long previous11Millis = 0;     // store last time 11LED was updated
long previous10Millis = 0;     // store last time 10LED was updated
long intervalmilli    = 10;       // interval at which to blink heartbeat (in milliseconds)
long intervalsecond   = 100;    // interval at which to blink seconds   (in milliseconds)
long intervalminute   = 1000;   // interval at which to blink minute    (in milliseconds)
long intervalhour     = 10000;   // interval at which to blink hours     (in milliseconds)


void setup() {
// Set up the digital pins as output
  pinMode(led13Pin, OUTPUT);
  pinMode(led12Pin, OUTPUT);
  pinMode(led11Pin, OUTPUT);
  pinMode(led10Pin, OUTPUT);
}


void loop()
{
  // Magic happens here, Here the Idea is to..
  //   1. Use the ping 13 LED as the Heartbeat of the Clock. It updates every 10 Milliseconds (0.01 Seconds)
  //   2. We check to see if it's time to blink the LED and/or Update the Clock, to do that we look at the
  //      difference between the current time and last time we blinked the LED

  // Get the "Current" Time
  // millis() - Returns the number of milliseconds since the Arduino board began running the current program.
  //            This number will overflow (go back to zero), after approximately 50 days.
  unsigned long currentMillis = millis();
  unsigned long current13Millis = currentMillis;
  unsigned long current12Millis = currentMillis;
  unsigned long current11Millis = currentMillis;
  unsigned long current10Millis = currentMillis;
  
  
  // Blink Pin 13 HEARTBEAT LED (on for "intervalmilli" milliseconds and off for "intervalmilli" seconds)
  if(current13Millis - previous13Millis > intervalmilli) {
    // save the last time you blinked the Pin 13 LED 
    previous13Millis = current13Millis;   
    // if the LED is off turn it on and vice-versa:
    if (led13State == LOW)
      led13State = HIGH;
    else
      led13State = LOW;
    // set the LED with the ledState of the variable:
    digitalWrite(led13Pin, led13State);
  }
  
  // Blink Pin 12 SECONDS LED (on for "intervalsecond" milliseconds and off for "intervalsecond" seconds)
  if(current12Millis - previous12Millis > intervalsecond) {
    // save the last time you blinked the LED 
    previous12Millis = current12Millis;   
    // if the LED is off turn it on and vice-versa:
    if (led12State == LOW)
      led12State = HIGH;
    else
      led12State = LOW;
    // set the LED with the ledState of the variable:
    digitalWrite(led12Pin, led12State);
  }
 
 // Blink Pin 1 MINUTES LED (on for "intervalminute" milliseconds and off for "intervalminute" milliseconds) 
    if(current11Millis - previous11Millis > intervalminute) {
    // save the last time you blinked the LED 
    previous11Millis = current11Millis;   
    // if the LED is off turn it on and vice-versa:
    if (led11State == LOW)
      led11State = HIGH;
    else
      led11State = LOW;
    // set the LED with the ledState of the variable:
    digitalWrite(led11Pin, led11State);
  }
 
  // Blink Pin 10 HOURS LED (on for "intervalhour" milliseconds and off for "intervalhour" milliseconds)
  if(current10Millis - previous10Millis > intervalhour) {
    // save the last time you blinked the LED 
    previous10Millis = current10Millis;   
    // if the LED is off turn it on and vice-versa:
    if (led10State == LOW)
      led10State = HIGH;
    else
      led10State = LOW;
    // set the LED with the ledState of the variable:
    digitalWrite(led10Pin, led10State);
  }
}
