#include <Servo.h>

// Define the servos
Servo MattServoLeft;
Servo MattServoRight;

// Variables

// Store servo position
int potpin = 0;
int val;
int number = 160;
int pad = 10;

void setup()
{
   MattServoLeft.attach(9); //attach servo to pin 9
   Serial.begin(9600);      // open serial port
   pinMode(5, OUTPUT);      // initialize digital pin as an output.
}

void loop()
 {
  //val = analogRead(potpin);
  //val = map(val, 0, 1023,0, 179);
  for (int i=0; i <= 1023; i+=pad){
    MattServoLeft.write(i);
    Serial.print(i);
    Serial.println("");
    delay(200);
   }
 }
