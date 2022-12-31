#include <Arduino.h>

void readButtons() {
  //read the buttons
  if (digitalRead(C1)) {money = money + 0.01;oldTime = time; ledblink(100);}
  if (digitalRead(C10)) {money = money + 0.10;oldTime = time; ledblink(100);}
  if (digitalRead(C25)) {money = money + 0.25;oldTime = time; ledblink(100);}
  if (digitalRead(S1)) {money = money + 1;oldTime = time; ledblink(100);}
}

void ledblink(int blinkTime) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkTime);
  digitalWrite(LED_BUILTIN, LOW);
}