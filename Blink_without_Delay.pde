/* Blink without Delay */
  
// set pin numbers:
const int ledPin =  13;      // the number of the LED pin
const int secPin =  12;      // the number of the LED pin
const int minPin =  11;      // the number of the LED pin
const int hourPin = 10;      // the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int secState = LOW;             // ledState used to set the LED
int minState = LOW;             // ledState used to set the LED
int hourState = LOW;            // ledState used to set the LED
int second = 0;
int minute = 0;
int hour = 0;
int secTimer = 0;
int minTimer = 0;
int hourTimer = 0;
long previousMillis = 0;        // will store last time LED was updated
long totalMillis = 0;           // how long the clock has been up, 0 since we just started it
int LITLED = 50;                // how long to stay lit

long interval = 1000;           // interval at which to blink (milliseconds)
long secinterval = 1000;        // One Second in milliseconds
long mininterval = 60000;       // One Minute in milliseconds
long hourinterval = 3500000;    // One Hour in milliseconds

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(secPin, OUTPUT);
  pinMode(minPin, OUTPUT);
  pinMode(hourPin, OUTPUT);
}

void loop()
{

  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    totalMillis = (currentMillis - previousMillis);

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) ledState = HIGH;
    else ledState = LOW;
    digitalWrite(ledPin, ledState);
    
    // update clock seconds
    if(totalMillis % 1000 == 0) {
        ++second;
        secState = HIGH;
        secTimer = totalMillis;
    }
    
    // update clock minutes
    if(totalMillis % 60000 == 0) {
        ++minute;
        minState = HIGH;
        minTimer = totalMillis;
    }
    
    // update clock hours
    if(totalMillis % 3600000 == 0) {
        ++hour;
        hourState = HIGH;
        hourTimer = totalMillis;
    }
    
    // turn off pins after LITLED milliseconds
    if(secTimer - totalMillis > LITLED) {
      secState = LOW;
    }
    if(minTimer - totalMillis > LITLED) {
      secState = LOW;
    }
    if(hourTimer - totalMillis > LITLED) {
      secState = LOW;
    }
  }
}
