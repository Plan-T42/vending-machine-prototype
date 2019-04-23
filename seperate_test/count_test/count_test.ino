/*
Adafruit Arduino - Lesson 14. Sweep
*/

#include <Servo.h> 


#define COUNTPin 8
#define OFFPin   7

int servoPin = 9;
 
Servo servo;  
 
int angle = 0;   // servo position in degrees 
int Switch = 0;
int count = 0;
int OffState = 0;
int lastOffState = 1;
int CountState = 0;
int lastCountState = 1;
 
void setup() 
{ 
  servo.attach(servoPin); 
  pinMode(COUNTPin, INPUT);
  pinMode(OFFPin, INPUT);
  digitalWrite(COUNTPin, HIGH);
  digitalWrite(OFFPin, HIGH);

  Serial.begin(9600);
} 
 
 
void loop() 
{
  OffState = digitalRead(OFFPin);
  CountState = digitalRead(COUNTPin);
  if (OffState != lastOffState)
  {
    Switch ++;
    Serial.println(Switch);
  }
  if (Switch / 2 % 2 == 1)
  {
    if (CountState != lastCountState) 
    {
      count++;
      Serial.println(count);
    }
  }
  else
  {
    for (int c = count / 2; c > 0; c--) 
    {
       // scan from 0 to 180 degrees
       for (angle = 0; angle < 90; angle++)  
      {                                  
        servo.write(angle);               
        delay(15);                   
      } 
      // now scan back from 160 to 0 degrees
      for (angle = 90; angle > 0; angle--)    
      {                                
        servo.write(angle);           
        delay(15);    
      }
    }
    count = 0;
  }
  lastOffState = OffState;
  lastCountState = CountState;
} 
