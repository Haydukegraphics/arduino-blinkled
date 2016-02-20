// Print random DEC to the serial port with blinky light w/o delays
// MS 03/19/2011

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
  Serial.begin(9600);   // open a serial port
  pinMode(13, OUTPUT);  // initialize digital pin as an output.
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
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
  
  // code to generate ramdom values for the data string (temp)
  int value1 = random(0, 255);  // random number for value 1
  int value2 = random(0, 255);  // random number for value 2
  int value3 = random(0, 255);  // random number for value 3
  
  // Construct a Message with multiple values. Can't send a string, Understands only 'bytes'
  // Send at timed intervals (intervalData)
  if(currentMillis - previousDataMillis > intervalData) {
    // save the last time we sent data
    previousDataMillis = currentMillis;
    // Send the Data
    Serial.print('H');              // any START OF STRING identifier
    Serial.print(',');              // string separator
    Serial.print(value1, DEC);      // print RAND DEC value #1
    Serial.print(",");
    Serial.print(value2, DEC);      // print RAND DEC value #2
    Serial.print(",");
    Serial.print(value3, DEC);      // print RAND DEC value #3
    Serial.print(',');              // string separator
    Serial.print(RandomLed, DEC);   // print Which Led modified
    Serial.print(",");
    Serial.print(rate, DEC);        // print Led Blinky rate
    Serial.print(",");              // string separator at the end
    Serial.println("");             // finish with \r\n
  }
}

