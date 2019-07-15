#include <SPI.h>
#include <Wire.h>
#include "time.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 128
#define HEIGHT 64

#define OLED_RESET -1

#define HEADER 'T'

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);
Time time(1, 4, 0);

unsigned long previousTime;

void setup()
{
  Serial.begin(9600);

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
    {
    } // stuck forever
  }

  // Clear the display of Adafruit logo
  display.clearDisplay();

  previousTime = millis();
}

void loop()
{
  // Update time
  updatetime();

  // Display time
  displaytime();
}

void updatetime()
{
  time.addMillis(millis() - previousTime);
  previousTime = millis();
}

void displaytime()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(WIDTH / 2 - 50, HEIGHT / 2);
  display.println(time.toString());

  display.display();
}