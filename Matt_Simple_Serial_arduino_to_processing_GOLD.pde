// print random strings to the serial port

// Golbal Variables, etc.
  int RandomLed     = 0;   // hold the random LED pin

void setup() {
  Serial.begin(9600);      // open serial port
  pinMode(13, OUTPUT);     // initialize digital pin as an output.
  pinMode(12, OUTPUT);     // same as above
  pinMode(11, OUTPUT);     // same as above
  pinMode(10, OUTPUT);     // same as above
}

void loop () {
  int value1 = random(0, 10);
  int value2 = random(0, 10);
  int value3 = random(0, 10);
  
  //construct a message with multiple values in arduino
  //we can't just send a string from here since it only officially understands 'bytes'
  Serial.print('H');           // any START OF STRING identifier
  Serial.print(',');           // string separator
  Serial.print(value1, DEC);
  Serial.print(",");           // string separator
  Serial.print(value2, DEC);
  Serial.print(",");           // string separator
  Serial.print(value3, DEC);
  Serial.print(",");           // a final string separator at the end
  Serial.println("");          // finish with \r\n
  delay(500);
  
  // Blink Random LED because who doesn't like blinky lights.
  RandomLed = random(10, 14);
  digitalWrite(RandomLed, HIGH); // set the LED on
  delay(250);
  digitalWrite(RandomLed, LOW); // set the LED off
  delay(250);
}
