#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define POT 0

#define WIDTH 128
#define HEIGHT 64

#define OLED_RESET -1

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

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
}

void loop()
{
    int val = analogRead(POT);

    val = map(val, 0, 1023, 0, 100);

    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.println(val);

    display.display();
}