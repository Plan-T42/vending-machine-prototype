#include <Servo.h>  //motor library

#include <SPI.h> // SPI-Library for RFID
#include <MFRC522.h> // RFID-Library for RFID

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

//IRSensor Pin
#define SENSORPin 9 

//Button Pins
#define STARTPin  12
#define FINISHPin 13

//RFID Pins
#define SS_PIN 53 // RFID SDA(SS)
#define RST_PIN 5 // RFID RST 
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

//Display Screen dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128 
//Display Pins
#define SCLK_PIN 2
#define MOSI_PIN 3
#define DC_PIN   4
#define CS_PIN   5
#define RST_PIN  6
// Display Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  


//Servo Pins
int coinServoPin = 11;
int cupServoPin = 8;
int boxServoPin = 10;

//Servo Objects
Servo coinServo; 
Servo cupServo;
Servo boxServo;

//Motor 
int angle = 0;   // servo position in degrees 

//buttons
int startState = 0; 
int startLastState = 1;
int finishState = 0;
int finishLastState = 1;

//rfid
int rfidState = 0;

//sensor
int count = 0;
int sensorState = 0;
int sensorLastState = 1;
 
void setup() 
{ 
  //Servo Motor
  coinServo.attach(coinServoPin); 
  cupServo.attach(cupServoPin);
  boxServo.attach(boxServoPin);
  coinServo.write(0);
  cupServo.write(0);
  boxServo.write(0);

  //IRSensor
  pinMode(SENSORPin, INPUT);
  digitalWrite(SENSORPin, HIGH);
  
  //Buttons
  pinMode(STARTPin, INPUT);
  pinMode(FINISHPin, INPUT);
  digitalWrite(STARTPin, HIGH);
  digitalWrite(FINISHPin, HIGH);

  //RFID
  SPI.begin(); // open SPI connection
  mfrc522.PCD_Init(); // Initialize Proximity Coupling Device (PCD)

  Serial.begin(9600); // open serial connection

  //Display
  tft.begin();
  uint16_t time = millis();
  tft.fillRect(0, 0, 128, 128, BLACK);
  time = millis() - time;
  
  Serial.println(time, DEC);
  delay(500);
  
  tft.fillScreen(BLACK);
  tft.setCursor(0, 5);
  tft.setTextColor(WHITE);  
  tft.setTextSize(3);
  tft.println("Hello  World!");
  
} 
 
 
void loop() 
{
  startState = digitalRead(STARTPin);
  finishState = digitalRead(FINISHPin);

  //check start button 
  if(!startState && startLastState)
  {
    Serial.println("start");
    
    tft.fillScreen(BLACK);
    tft.setCursor(0, 5);
    tft.setTextColor(WHITE);  
    tft.setTextSize(3);
    tft.println("ReWert Journey starts!");
    
    while (1)
    {
      //check IR sensor 
      sensorState = digitalRead(SENSORPin);
      //Serial.println(sensorState);
    
      if( !sensorState && sensorLastState)
      {   
        Serial.println("IRsensor detected");

        //check RFID
        if (mfrc522.PICC_IsNewCardPresent())
        {
          //with RFID => box
          Serial.println("box");

          tft.fillScreen(BLACK);
          tft.setCursor(0, 5);
          tft.setTextColor(WHITE);  
          tft.setTextSize(2);
          tft.println("Oh, a box!");
          
          
          //move box motor
          for(angle = 0; angle < 180; angle++)  
          {                                  
          boxServo.write(angle);               
          delay(10);                   
          } 
          // now scan back from 180 to 0 degrees
          for(angle = 180; angle > 0; angle--)    
          {                                
          boxServo.write(angle);           
          delay(10);       
          } 
            //delay(1000);        
            //boxServo.write(180);               
            //delay(1000);                   
            //boxServo.write(0);                  
        }     
        else
        {
          //without RFID => cup
          Serial.println("cup");

          tft.fillScreen(BLACK);
          tft.setCursor(0, 5);
          tft.setTextColor(WHITE);  
          tft.setTextSize(2);
          tft.println("Oh, a cup!");

          
          //move cup motor
          for(angle = 0; angle < 180; angle++)  
          {                                  
          cupServo.write(angle);               
          delay(5);                   
          } 
          // now scan back from 180 to 0 degrees
          for(angle = 180; angle > 0; angle--)    
          {                                
          cupServo.write(angle);           
          delay(5);       
          } 
                    
          //move cup motor
          //delay(1000);
          //cupServo.write(180);               
          //delay(1000);                   
          //cupServo.write(0);  
        }

        //count coin 
        count++;
        tft.setCursor(0,80);
        Serial.print("count:");
        Serial.println(count);

        tft.setTextColor(YELLOW);  
        tft.setTextSize(2);
        tft.print("  count:");
        tft.println(count);
      }

      sensorLastState = sensorState;
      
      if ( !digitalRead(FINISHPin))
      {
        break;
      }
    }
  }
    
  //check finish state
  if( !finishState && finishLastState)
  {
    Serial.print(count);
    Serial.println(" coin(s) out!");

    tft.fillScreen(BLACK);
    tft.setCursor(0, 5);
    tft.setTextColor(WHITE);  
    tft.setTextSize(2);
    tft.print(count);
    tft.println(" coin(s) coming!");

    //coin coming!
    for (int c = count; c > 0; c--) 
    {
        for(angle = 0; angle < 50; angle++)  
        {                                  
        coinServo.write(angle);               
        delay(50);                   
        } 
        // now scan back from 180 to 0 degrees
        for(angle = 50; angle > 0; angle--)    
        {                                
        coinServo.write(angle);           
        delay(50);       
        } 
        //coinServo.write(180);               
        //delay(1000);                   
        //coinServo.write(0); 
        //delay(1000); 
    }
    count = 0;
  }
  
  //update button state
  startLastState = startState;
  finishLastState = finishState;
}
