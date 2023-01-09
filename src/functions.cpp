#include <Arduino.h>
#include <EEPROM.h>
#include "functions.hpp"

const int C1 = 10; // adds 1 cent
const int C10 = 9; // adds 10 cents
const int C25 = 8; // adds 25 cents
const int S1 = 7;  // adds 1 dollar
const int addr = 0;
unsigned long time = millis();
unsigned long oldTime = time;
bool add = true;
float money;
float oldMoney;
float wantMoney;

void multiBlink(int blinkTime, int blinkNumber) {
  for (int i = 0; i < blinkNumber; i++) {
    ledBlink(blinkTime);
    delay(blinkTime);
  }
}

void ledBlink(int blinkTime) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkTime);
  digitalWrite(LED_BUILTIN, LOW);
}

float readButtons() {
  // read the buttons
  float to_add = 0;
  if (digitalRead(C1) == 0)  {to_add += 0.01;}
  if (digitalRead(C10) == 0)  {to_add += 0.10;}
  if (digitalRead(C25) == 0)  {to_add += 0.25;}
  if (digitalRead(S1) == 0)  {to_add += 1;}

  if (add == false) {to_add *= -1;}
  if (!digitalRead(C1) || !digitalRead(C10) || !digitalRead(C25) || !digitalRead(S1)) {
    digitalWrite(LED_BUILTIN, HIGH);
    while (!digitalRead(C1) || !digitalRead(C10) || !digitalRead(C25) || !digitalRead(S1)) {delay(1);}
    digitalWrite(LED_BUILTIN, LOW);
  }
  if (to_add != 0) {oldTime = time;}
  return to_add;
}

void setupPins() {
  // set the pin states
  pinMode(C1, INPUT_PULLUP);
  pinMode(C10, INPUT_PULLUP);
  pinMode(C25, INPUT_PULLUP);
  pinMode(S1, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void subtractMode() {add = false;}
void addMode() {add = true;}