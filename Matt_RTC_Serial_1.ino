// Add LCD Library
#include <LiquidCrystal.h>

// Define the pins the LCD uses.
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int command = 0;  // This is the command char, in ascii form, sent from the serial port     
long previousMillis = 0;  // will store last time Temp was updated
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
byte test;

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}



void setup()
{
  Serial.begin(9600);             // open a serial port  
}

void loop() {
  if (Serial.available()) {  // Look for char in serial que and process if found
    command = Serial.read();
    if (command == 84) {      //If command = "T" Set Date
      setDateDs1307();
      getDateDs1307();
      Serial.println(" ");
    }
    else if (command == 81) {  //If command = "Q" RTC1307 Memory Functions
      delay(100);     
      if (Serial.available()) {
        command = Serial.read(); 
        
        // If command = "1" RTC1307 Initialize Memory - All Data will be set to 255 (0xff).  
        // Therefore 255 or 0 will be an invalid value.  
        if (command == 49) { 
          
          // 255 will be the init value and 0 will be cosidered an error that 
          // occurs when the RTC is in Battery mode. 
          Wire.beginTransmission(clockAddress);
          
          // Set the register pointer to be just past the date/time registers.
          Wire.write(byte(0x08));  
          for (int i = 1; i <= 27; i++) {
            Wire.write(byte(0xff));
            delay(100);
          }   
          Wire.endTransmission();
          getDateDs1307();
          Serial.println(": RTC1307 Initialized Memory");
        }
        else if (command == 50) {      //If command = "2" RTC1307 Memory Dump
          getDateDs1307();
          Serial.println(": RTC 1307 Dump Begin");
          Wire.beginTransmission(clockAddress);
          Wire.write(byte(0x00));
          Wire.endTransmission();
          Wire.requestFrom(clockAddress, 64);
          for (int i = 1; i <= 64; i++) {
            test = Wire.read();
            Serial.print(i);
            Serial.print(":");
            Serial.println(test, DEC);
          }
          Serial.println(" RTC1307 Dump end");
        } 
      }  
    }
    Serial.print("Command: ");
    Serial.println(command);  // Echo command CHAR in ascii that was sent
  }

  command = 0;  // reset command                  
  delay(100);
}
