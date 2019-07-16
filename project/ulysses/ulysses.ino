#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdio.h>
#include <RTClib.h>

#define WIDTH 128
#define HEIGHT 64

#define OLED_RESET -1

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);
DateTime dt(__DATE__, __TIME__);
float previousTime;
int milli;

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
  milli += millis() - previousTime;
  int seconds = dt.second() + (milli / 1000);  
  int minutes = dt.minute() + (seconds / 60);
  int hour = dt.hour() + (minutes / 60);

  milli %= 1000;
  seconds %= 60;
  minutes %= 60;
  hour %= 24;

  dt = DateTime(dt.year(), dt.month(), dt.day(), hour, minutes, seconds);

  previousTime = millis();
}

void displaytime()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(WIDTH / 2 - 50, HEIGHT / 2);

  display.print(dt.hour());
  display.print(":");
  display.print(dt.minute());
  display.print(":");
  display.println(dt.second());

  display.display();
}