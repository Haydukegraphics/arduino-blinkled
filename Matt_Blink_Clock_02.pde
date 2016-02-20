/* Matt Blink Clock S
 
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
const int HeartBeatPin =  13;   // Heardbeat
const int SecondPin    =  12;   // Seconds
const int MinutePin    =  11;   // Minutes
const int HourPin      =  10;   // Hours

// Variables
// Load Initial States, 0 out counters, set intervals
int HeartBeatState     = LOW;   // led13State used to set the LED 13
int SecondState        = LOW;   // led12State used to set the LED 12
int MinuteState        = LOW;   // led11State used to set the LED 11
int HourState          = LOW;   // led10State used to set the LED 10
long previousHeartBeat = 0;     // store last HeartBeat
long previousSecond    = 0;     // store last Second
long previousMinute    = 0;     // store last Minute
long previousHour      = 0;     // store last Hour
long intervalHeartBeat = 10;    // heartbeat (in milliseconds)
long intervalSecond    = 10;    // seconds   (in milliseconds)
long intervalMinute    = 100;   // minute    (in milliseconds)
long intervalHour      = 1000;  // hours     (in milliseconds)

void setup() {
  
  // Set up the digital pins as output
  pinMode(HeartBeatPin, OUTPUT);
  pinMode(SecondPin, OUTPUT);
  pinMode(MinutePin, OUTPUT);
  pinMode(HourPin, OUTPUT);

}


void loop() {

  // millis() - the number of milliseconds since the Arduino began running the current program
  unsigned long currentbeat      = millis();
  unsigned long currentHeartBeat = currentbeat;
  unsigned long currentSecond    = currentbeat;
  unsigned long currentMinute    = currentbeat;
  unsigned long currentHour      = currentbeat;
  
  // HEARTBEAT
  if(currentHeartBeat - previousHeartBeat > intervalHeartBeat) {
    
    // save the last time you updaated the heartbeat
    previousHeartBeat = currentHeartBeat;  
    
    // if the LED is off turn it on and vice-versa:
    if (HeartBeatState == LOW)
        HeartBeatState = HIGH;
    else
        HeartBeatState = LOW;
        
    // update the HeartBeat's Pin State
    digitalWrite(HeartBeatPin, HeartBeatState);
    
   }
  
  // SECONDS Pin
  if(currentSecond - previousSecond > intervalSecond) {
    
    // save the last time you blinked the LED 
    previousSecond = currentSecond;   
    
    // if the LED is off turn it on and vice-versa:
    if (SecondState == LOW)
        SecondState = HIGH;
    else
        SecondState = LOW;
        
    // update the Second's Pin State
    digitalWrite(SecondPin, SecondState);
    
  }
 
 // MINUTES 
    if(currentMinute - previousMinute > intervalMinute) {
      
    // save the last time you blinked the LED 
    previousMinute = currentMinute;  
    
    // if the LED is off turn it on and vice-versa:
    if (MinuteState == LOW)
        MinuteState = HIGH;
    else
        MinuteState = LOW;
      
    // update the Minute's Pin State
    digitalWrite(MinutePin, MinuteState);
    
  }
 
  // HOURS
  if(currentHour - previousHour > intervalHour) {
    
    // save the last time you blinked the LED 
    previousHour = currentHour;
    
    // if the LED is off turn it on and vice-versa:
    if (HourState == HIGH;)
        HourState = LOW;
    else
        HourState = LOW;
        
    // update the Hour's Pin Stateh
    digitalWrite(HourPin, HourState);
  }
}
