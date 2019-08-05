#include <Adafruit_CircuitPlayground.h>
#include "MIDIUSB.h"

#define DEBOUNCE 500

const int button = 4;

boolean activated(uint8_t sensor) {
  return digitalRead(sensor) == HIGH;  
}

void matchDrum(uint8_t sensor) {
  Serial.print("SENSOR: "); 
  Serial.println(sensor);
  Serial.print("Sending MIDI: ");

  switch (sensor) {
    case button:
      Serial.println("36. Kick drum.");
      playDrum(36);
      break;
    default:
      Serial.println("INVALID NOTE");
  }
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void playDrum(byte drum) {
  noteOn(9, drum, 125);
  MidiUSB.flush();
  noteOff(9, drum, 0);
  MidiUSB.flush();
}

void setup() {
  // Initialize serial.
  Serial.begin(9600);

  // Set inbuilt button to read input.
  pinMode(button, INPUT);

  // Initialize Circuit Playground library.
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (activated(button)) {
    // Play appropriate drum sound.
    matchDrum(button);

    // Add debounce to avoid continous sensor reading.
    delay(DEBOUNCE);
  }
}
