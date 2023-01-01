#include <Arduino.h>
#include <EEPROM.h>
#include "functions.hpp"

void ledBlink(int blinkTime) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkTime);
  digitalWrite(LED_BUILTIN, LOW);
}

void eepromClear() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

void readButtons() {
  //read the buttons
  float to_add = 0;
  if (add == true) {
    if (digitalRead(C1)) {to_add = to_add + 0.01;}
    if (digitalRead(C10)) {to_add = to_add + 0.10;}
    if (digitalRead(C25)) {to_add + to_add + 0.25;}
    if (digitalRead(S1)) {to_add = to_add + 1;}
  } else {
    if (digitalRead(C1)) {to_add = to_add - 0.01;}
    if (digitalRead(C10)) {to_add = to_add - 0.10;}
    if (digitalRead(C25)) {to_add = to_add - 0.25;}
    if (digitalRead(S1)) {to_add = to_add - 1;}
  }

  money = money + to_add;
  oldTime = time;
  ledBlink(100);
}
