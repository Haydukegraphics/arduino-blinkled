// Print random DEC to the serial port with blinky light w/o delays
// MS 03/19/2011

// Global Variables
int ledState            = LOW;  // ledState used to set the LED
long previousLedMillis  = 0;    // will store last time LED was updated
long previousDataMillis = 0;    // will store last time LED was updated
long intervalLed        = 60;   // interval at which to blink Led (milliseconds)
long intervalData       = 5000; // interval at which to send data (milliseconds)

void setup() {
  Serial.begin(9600);   // open a serial port
  pinMode(13, OUTPUT);  // initialize digital pin as an output.
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop () {
  int value1 = random(0, 255);            // random number for value#
  int value2 = random(0, 255);
  int value3 = random(0, 255);
  unsigned long currentMillis = millis(); // get current time

  // Construct a Message with multiple values. Can't send a string, Understands only 'bytes'
  // Send at timed intervals (intervalData)
  if(currentMillis - previousDataMillis > intervalData) {
    // save the last time we sent data
    previousDataMillis = currentMillis;
    // Send the Data
    Serial.print('H');           // any START OF STRING identifier
    Serial.print(',');           // string separator
    Serial.print(value1, DEC);   // print DEC value
    Serial.print(",");
    Serial.print(value2, DEC);
    Serial.print(",");
    Serial.print(value3, DEC);
    Serial.print(",");           // string separator at the end
    Serial.println("");          // finish with \r\n
  }

  // Blink Random LED because who doesn't like blinky lights.
  // pick a Led pin
  int RandomLed = random(10, 14);
  // See if its time to update
  if(currentMillis - previousLedMillis > intervalLed) {
    // Save the last time we blinked the LED
    previousLedMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) ledState = HIGH;
    else ledState = LOW;
    // set the LED with the ledState of the variable:
    digitalWrite(RandomLed, ledState);
  }
}

