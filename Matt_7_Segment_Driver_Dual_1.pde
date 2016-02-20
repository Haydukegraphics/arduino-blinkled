// Drive a Dual 7-Segment Display
// Matt Simmons: 11/20/2011

// Bits that represent the numbers
const byte numeral1[10] = {
  // ABCDEFG and dp
  B11111011, // 0
  B01100000, // 1
  B11011101, // 2
  B11110101, // 3
  B01100110, // 4
  B10110110, // 5
  B00111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11100110, // 9
};

const byte numeral2[10] = {
  // ABCDEFG and dp
  B11111011, // 0
  B01100000, // 1
  B11011101, // 2
  B11110101, // 3
  B01100110, // 4
  B10110110, // 5
  B00111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11100110, // 9
};

// Pins for each number and dec point.
//                          dp,G,F,E,D,C,B,A
const int segmentPins1[8] = {5,9,8,7,6,4,3,2};
const int segmentPins2[8] = {14,17,16,15,13,12,11,10};

void setup ()
 {
   for (int i = 0; i < 8; i++)
   {
     pinMode(segmentPins1[i], OUTPUT); // set segment and DP pins to output
     pinMode(segmentPins2[i], OUTPUT);
   }
 }
 
 void loop()
 {
   for (int i = 0; i <= 9; i++)
   {
     showDigit1(i);
     showDigit2(i);
     delay(1000); // one sec
   }
 }
 
 // Display the number in segment 1
 void showDigit1(int number)
 {
   boolean isBitSet;
 
   for (int segment = 1; segment < 8; segment++)
   {
     if (number < 0 || number > 9) {
       isBitSet = 0; // turn off all segments
     }
     else {
       // isBitSet will be true is given bit is 1
       isBitSet = bitRead(numeral1[number], segment);
     }
     isBitSet = ! isBitSet; // WTF? For Anode 7-Segment LEDs
     digitalWrite(segmentPins1[segment], isBitSet);
   }
 }
   
 // Display the number in segment 2
 void showDigit2(int number)
 {
   boolean isBitSet;
 
   for (int segment = 1; segment < 5; segment++)
   {
     if (number < 0 || number > 9) {
       isBitSet = 0; // turn off all segments
     }
     else {
       // isBitSet will be true is given bit is 1
       isBitSet = bitRead(numeral2[number], segment);
     }
     isBitSet = ! isBitSet; // WTF?
     digitalWrite(segmentPins2[segment], isBitSet);
   }
 }
