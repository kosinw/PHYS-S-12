#include <Adafruit_CircuitPlayground.h>
#include "MIDIUSB.h"

#define DEBOUNCE 250

//const int PALM = 0;
const int TEST = 0;
const int PINKY = 1;

const int N = 100;

const int threshold = -300;

const int digits[] = {4, 9};
const int numDigits = sizeof(digits) / sizeof(int);
boolean previousState[numDigits];

const int KICK = 0;
const int SNARE = 1;
const int FLOOR_TOM = 2;
const int RIDE = 3;
const int TOM1 = 4;
const int TOM2 = 5;

const int drums[] = {36, 38, 41, 48, 45, 43};
const int numDrums = sizeof(drums) / sizeof(int);

boolean processDigit(int num);
void playNote(int num);
void note(byte drum);
void noteOn(byte channel, byte pitch, byte velocity);
void noteOff(byte channel, byte pitch, byte velocity);

int currentDrum = 0;

void setup() {
  // Initialize serial.
  Serial.begin(9600);

  // Set all pins that are used for sensors (or testing) as input.
  for (int i = 0; i < numDigits; ++i) {
    pinMode(digits[i], INPUT);
  }

  // Ensure (even though i'm reasonably sure) that previousStates is zeroed out.
  memset(previousState, 0, sizeof(previousState));

  // Initialize Circuit Playground library.
  CircuitPlayground.begin();
}

void loop() {
  // Process each digit.
  boolean shouldDebounce = false;
  
  for (int i = 0; i < numDigits; ++i) {
    shouldDebounce |= processDigit(i);
  }

  // If at least one sensor was activated, then debounce
  if (shouldDebounce) {
    delay(DEBOUNCE);
  }
}

boolean processDigit(int num) {
  // Read the value
  int value = 0;
  for (int i = 0; i < N; ++i) {
    value += analogRead(digits[num]);
  }
  value /= N;

  // Play the note if light level is below a certain threshold.
  boolean play = value < threshold;
  
  // If this pin is TEST, then just read digital input.
  if (num == TEST) {
    play = digitalRead(digits[TEST]) == HIGH;
  }

  // Play if the conditions of play have been met, and the sensors was not activated the last loop cycle.
  if (play && previousState[num] != play) {
    playNote(num);
  }

  previousState[num] = play;
}

void playNote(int num) {
  Serial.print("SENSOR #: ");
  Serial.println(num);
  Serial.print("Sending MIDI: ");
  
  switch (num) {
    case TEST:      
      currentDrum++;
      currentDrum %= numDrums;
    case PINKY:
      Serial.println(drums[currentDrum]);
      note(drums[currentDrum]);      
    default:
      Serial.println("INVALID NOTE.");
  }
}

void note(int drum) {
  noteOn(9, drum, 125);
  MidiUSB.flush();
  noteOff(9, drum, 0);
  MidiUSB.flush();
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}