#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
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
  lcd.begin(16,2);               // initialize the lcd 

  lcd.home ();                   // go home
  lcd.print("-- Blue Robot --");  
  lcd.setCursor (6, 1);        // go to the second (1) line and 6 over
  lcd.print (" Sec:");      
}

void loop()
{
 lcd.setCursor(11,1);            // move cursor to second line "1" and 13 spaces over
 lcd.print(millis()/1000);      // display seconds elapsed since power-up

 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     lcd.print("RIGHT ");
     delay(1000);
     break;
     }
   case btnLEFT:
     {
     lcd.print("LEFT  ");
     delay(1000);
     break;
     }
   case btnUP:
     {
     lcd.print("UP    ");
     delay(1000);
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     delay(1000);
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT");
     delay(1000);
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;
     }
   }
 }

