// Add LCD Library
#include <LiquidCrystal.h>
// Add Servo Library
#include <Servo.h>

// Define the pins the LCD uses.
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Global Variables
long previousDataMillis       = 0;     // store last time Data was sent
long previousServoWheelMillis = 0;     // store last time cont rotation Servos were moved
long intervalData             = 5000;  // interval at which to send data (milliseconds)
long intervalWheelServo       = 10000; // interval at which to move servo (milliseconds)
Servo servoLEFTWheel;              // define cont rotation servo1
Servo servoRIGHTWheel;             // define cont rotation servo2
// Define values used by the LCD Panel and LCD Buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons (subroutine)
int read_LCD_buttons()
{
 adc_key_in = analogRead(0); // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741. We add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
 return btnNONE;  // when all others fail, return this...
}

void setup()
{
  Serial.begin(9600);             // open a serial port
  servoLEFTWheel.attach(2);   // pin for cont rotation servro1
  servoRIGHTWheel.attach(3);  // pin for cont rotation servro2
  lcd.begin(16,2);        // initialize the lcd 

  lcd.home (); // go home
  lcd.print("Blue");  
  lcd.setCursor (12, 0);  // go to the second (1) line and 6 over
  lcd.print (" Sec:");      
}

void loop()
{ 
 unsigned long currentMillis = millis(); // Get the current time
    
  // UPDATE THE DISPLAY WITH THE NEW DATA COMING FROM SENSORS
  // code to generate ramdom values for the data string (temp)
  int value1 = random(0, 255);  // random number for value 1
  int value2 = random(0, 255);  // random number for value 2
  int value3 = random(0, 255);  // random number for value 3
  int value4 = random(0, 255);  // random number for value 4
  int value5 = random(0, 255);  // random number for value 5
  
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
    Serial.print(',');
    Serial.print(value4, DEC);      // print RAND DEC value #4
    Serial.print(',');
    Serial.print(value5, DEC);      // print RAND DEC value #5
    Serial.println("");             // finish with \r\n
  } 
    
 // 
 lcd.setCursor(8,0);           // move cursor to second line "1" and 13 spaces over
 lcd.print(millis()/1000);      // display seconds elapsed since power-up

 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
       lcd.setCursor(0,1);
       lcd.print("Volts:");
       lcd.setCursor(9,1);
       lcd.print(value1);
     delay(1000);
     break;
     }
   case btnLEFT:
     {
     lcd.setCursor(0,1);
     lcd.print("Temp: ");
     lcd.setCursor(9,1);
     lcd.print(value2);
     delay(1000);
     break;
     }
   case btnUP:
     {
     lcd.setCursor(0,1);
     lcd.print("Speed:");
     lcd.setCursor(9,1);
     lcd.print(value3);
     delay(1000);
     break;
     }
   case btnDOWN:
     {
     lcd.setCursor(0,1);
     lcd.print("Light:");
     lcd.setCursor(9,1);
     lcd.print(value4);
     delay(1000);
     break;
     }
   case btnSELECT:
     {
     lcd.setCursor(0,1);
     lcd.print("Amps:  ");
     lcd.setCursor(9,1);
     lcd.print(value5);
     delay(1000);
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE            ");
     break;
     }
   }
 }

