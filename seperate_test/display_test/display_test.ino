#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_SSD1351.h>     // Hardware-specific library

//Display Screen dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128 

//Display Pins
#define SCLK_PIN 2
#define MOSI_PIN 3
#define DC_PIN   4
#define CS_PIN   5
#define RST_PIN  6

// Color definitions
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF


Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  
//float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  tft.begin();
  uint16_t time = millis();
  tft.fillRect(0, 0, 128, 128, BLACK);
  time = millis() - time;
  
  Serial.println(time, DEC);
  delay(500);
  
  tft.fillScreen(BLACK);
  tft.setCursor(0, 5);
  tft.setTextColor(WHITE);  
  tft.setTextSize(5);
  tft.println("Hello World!");
  
  }

  
void loop() {
}
