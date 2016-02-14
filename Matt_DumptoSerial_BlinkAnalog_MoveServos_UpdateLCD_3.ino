/ Print random DEC to the serial port with blinky light w/o delays and run two servos
// MS 03/01/2012

// Add Servo Libs.
#include <Servo.h>

// Global Variables
int ledState                  = LOW;   // ledState used to set the LED
long previousLedMillis        = 0;     // store last time LED was updated
long previousDataMillis       = 0;     // store last time Data was sent
long previousServoMillis      = 0;     // store last time Servo were moved
long previousServoWheelMillis = 0;     // store last time cont rotation Servos were moved
// long intervalLed           = 60;    // interval at which to blink Led (milliseconds)
long intervalData             = 5000;  // interval at which to send data (milliseconds)
long intervalServo            = 1000;  // interval at which to move servo (milliseconds)
long intervalWheelServo       = 10000; // interval at which to move servo (milliseconds)
const int sensorPin           = 0 ;    // Input for freq of blinky
const int minDuration         = 60;    // min Led blinky rate
const int maxDuration         = 1000;  // max Led blinky rate
int angleservo                = 0;     // store the servo position
int anglecont                 = 0;     // store the servo position
int pos                       = 0;     // store where is the server located
int forward                   = 0;     // store what direction we are traveling (1=forward, 2=backward)

Servo MattservoLEFT;                   // define servo1
Servo MattservoRIGHT;                  // define servo2
Servo MattservoLEFTWheel;              // define cont rotation servo1
Servo MattservoRIGHTWheel;             // define cont rotation servo2

void setup() {
  Serial.begin(9600);                  // open a serial port
  pinMode(13, OUTPUT);                 // initialize digital pin as an output.
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  MattservoLEFT.attach(6);             // pin for servo1
  MattservoRIGHT.attach(5);            // pin for servo2
  MattservoLEFTWheel.attach(2);        // pin for cont rotation servro1
  MattservoRIGHTWheel.attach(3);       // pin for cont rotation servro2
}

void loop () {
  
  unsigned long currentMillis = millis(); // Get the current time
  
  // UPDATE THE CONTINIOUS BLINKY LED (because who doesn't like blinky lights.)
  int RandomLed = random(10, 14); // pick a led
  
  // See if its time to update led state
  int rate = analogRead(sensorPin);  // read the analog pin for a value
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
  
  // UPDATE THE DISPLAY WITH THE NEW DATA COMING FROM SENSORS
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
  
  // UPDATE THE SERVOS (for the arms)
  if(currentMillis - previousServoMillis > intervalServo) {
  // save the last time we moved the servos (1 and 2)
  previousServoMillis = currentMillis;
  angleservo = random(0,180);
  MattservoRIGHT.write(angleservo); // go to position "angle"
  MattservoLEFT.write(angleservo);
  } 
  
  // UPDATE THE CONTINIOUS ROTATION SERVOS (for the wheels)
  int forward = random(0, 2);  // random number
  if(currentMillis - previousServoWheelMillis > intervalWheelServo) {
  // save the last time we moved the cont rotation servos (3 and 4)
  previousServoWheelMillis = currentMillis;
  switch (forward) { // 0 = full speed one way, 90 = stop, 180 = full speed the other
    case 0:
      anglecont = 0; // forward
        MattservoRIGHTWheel.write(anglecont);
        MattservoLEFTWheel.write(180-anglecont);
        anglecont = 90;
        break;
    case 1:
      anglecont = 180; // reverse
        MattservoRIGHTWheel.write(180-anglecont);
        MattservoLEFTWheel.write(anglecont);
        anglecont = 90;
        break;
    case 2:
      anglecont = 90; // stop 
        MattservoRIGHTWheel.write(180-anglecont);
        MattservoLEFTWheel.write(anglecont);
        anglecont = 0;
        break;
   }
  }
}
