
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

  #define TFT_CS        17
  #define TFT_RST       20
  #define TFT_DC        21

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
int lastNeedleX = 120;
int lastNeedleY = 140;
int indicatorX = 200;
int indicatorY = 40;
int indicatorRadius = 25;
int WarnVal = 80; // set this to set when the warning light is on

void setup(void) {
 
  Serial.begin(9600);
  tft.init(240, 280);           // Init ST7789 280x240
  tft.setSPISpeed(40000000);
  tft.fillScreen(ST77XX_BLACK);
  tft.drawCircle(120, 140, 100, ST77XX_WHITE); // outer circle
  tft.drawCircle(120, 140, 101, ST77XX_WHITE); // outer circle
  tft.drawCircle(120, 140, 102, ST77XX_WHITE); // outer circle
  tft.drawCircle(indicatorX, indicatorY, indicatorRadius, ST77XX_WHITE);
  for (int i = -135; i <= 135; i += 45) {
    float tickAngle = i * 0.0174533;
    int x0 = 120 + cos(tickAngle) * 93;
    int y0 = 140 + sin(tickAngle) * 93;
    int x1 = 120 + cos(tickAngle) * 100;
    int y1 = 140 + sin(tickAngle) * 100;
    tft.drawLine(x0, y0, x1, y1, ST77XX_MAGENTA);
    tft.drawLine(x0+1, y0, x1+1, y1, ST77XX_MAGENTA);
  }
}

void loop() {
  for (int i = 0; i <= 100; i++) {
    drawGauge(i);
   delay(50);
  }
  for (int i = 100; i >= 0; i--) {
    drawGauge(i);
   delay(50);
  }
}
void drawGauge(int value) {
  // Erase previous needle (draw over with black - 3px wide)
  for (int i = -1; i <= 1; i++) {
    tft.drawLine(120 + i, 140, lastNeedleX + i, lastNeedleY, ST77XX_BLACK);
  }

(0-100) to angle (-135° to +135°)
float angle = ((value / 100.0) * 270.0 - 135.0) * 0.0174533; 

  // New needle endpoint
  int x = 120 + cos(angle) * 90;
  int y = 140 + sin(angle) * 90;
  for (int i = -1; i <= 1; i++) {
    tft.drawLine(120 + i, 140, x + i, y, ST77XX_RED);
  }

  // Update stored needle position
  lastNeedleX = x;
  lastNeedleY = y;
  tft.fillCircle(120, 140, 5, ST77XX_WHITE);
 
  if (value > WarnVal) {
    tft.fillCircle(indicatorX, indicatorY, indicatorRadius-1, ST77XX_RED);
  }else{
      tft.fillCircle(indicatorX, indicatorY, indicatorRadius-1, ST77XX_BLACK);
  }
}

