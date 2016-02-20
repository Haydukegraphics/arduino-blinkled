#include <Servo.h>

Servo MattservoLEFT;   // define servo objects
Servo MattservoRIGHT;

int angle = 0;         // store the servo position

void setup()
{
   MattservoLEFT.attach(6);   // what pin is the server on
   MattservoRIGHT.attach(5);
}

void loop()
{
  angle = random(0,180);
  #for(angle = 0; angle < 180; angle += 1) // go from 0 to 180 degrees in steps of one degree
  #{
      MattservoRIGHT.write(angle); // go to position "angle"
      MattservoLEFT.write(angle);
      delay(20);
  #}
  #for(angle = 180; angle >= 1; angle -= 1) // go from 180 to 0 degrees in steps of one degree
  #{
      MattservoRIGHT.write(angle); // go to position "angle"
      MattservoLEFT.write(angle);
      delay(20);
  #}
} 
