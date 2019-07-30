
/*
  Simple sketch for nRF24L01+ radios  Receive side.

  Updated: Dec 2014 by TMRh20. Simplified Mar 2019 RMH.
*/

#include <SPI.h>
#include <Wire.h>
#include "RF24.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define WIDTH 128
#define HEIGHT 64
#define OLED_RESET -1

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7, 8);

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

byte addresses[][6] = {"1Kosi", "2Kosi"};

void print_monitor(int val) {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(val);

  display.display();
}

void setup() {

  Serial.begin(115200);
  Serial.println(F("RF24example:  simple receive"));
  //myservo.attach(2);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
    {
    } // stuck forever
  }

  // Clear the display
  display.clearDisplay();

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);


  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() {

  byte rec_data;

  if ( radio.available()) {
    // Variable for the received timestamp
    while (radio.available()) {                                   // While there is data ready
      radio.read( &rec_data, 1 );             // Get the payload
    }
    print_monitor(rec_data);
    Serial.print("received ");
    Serial.println(rec_data);
  }
} // Loop
