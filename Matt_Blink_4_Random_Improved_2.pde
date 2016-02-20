/*
  Matt's First Blink
  Turns on an LED on for one second, then off, repeatedly.
 */
 
  // Variables
  int RandomLed     = 0;
  int RandomNumber  = 0;
  //int value1        = 1;
  //int value2        = 2;
  //int value3        = 3;
  String DataString = "";

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(10, OUTPUT);   
}

  void loop() {
    
    // start the Serial communication
    Serial.begin(9600);
     
    // blink a random led for fun
    RandomLed = random(10, 14);
    digitalWrite(RandomLed, HIGH); // set the LED on
    delay(500);
    digitalWrite(RandomLed, LOW); // set the LED off
    delay(500);
    
    // print a random number to the serial port
    // RandomNumber = random(0, 10);
    // Serial.println(RandomNumber, BYTE);
    //delay(1000);
    int value1 = random(0, 10);
    int value2 = random(0, 10);
    int value3 = random(0, 10);
    Serial.print(value1, DEC);
    Serial.print(",");
    Serial.print(value2, DEC);
    Serial.print(",");
    Serial.print(value3, DEC);
    Serial.println("|");
  }
