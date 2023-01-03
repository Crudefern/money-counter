#include <Arduino.h>
#include <EEPROM.h>
#include "functions.hpp"

const int C1=10; //adds 1 cent
const int C10=9; //adds 10 cents
const int C25=8; //adds 25 cents
const int S1=7;  //adds 1 dollar
const int addr = 0;
unsigned long time = millis();
unsigned long oldTime = time;
bool add = true;
float money;
float oldMoney;

void multiBlink(int blinkTime,int blinkNumber) {
  for (int i = 0;i < blinkNumber;i++) {
    ledBlink(blinkTime);
    delay(blinkTime);
  }
}

void ledBlink(int blinkTime) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkTime);
  digitalWrite(LED_BUILTIN, LOW);
}

void eepromClear() {
  money = 0;
  // EEPROM.put(addr,money);
  multiBlink(500,5);
}

void readButtons() {
  //read the buttons
  float to_add = 0;

  if (digitalRead(C1) == 0) {to_add += 0.01;}
  if (digitalRead(C10) == 0) {to_add += 0.10;}
  if (digitalRead(C25) == 0) {to_add += 0.25;}
  if (digitalRead(S1) == 0) {to_add += 1;}
  if (add == true) {money += to_add;} else {money -= to_add;}
  oldTime = time;

  if (!digitalRead(C1) || !digitalRead(C10) || !digitalRead(C25) || !digitalRead(S1)) {
    digitalWrite(LED_BUILTIN,HIGH);
    while (!digitalRead(C1) || !digitalRead(C10) || !digitalRead(C25) || !digitalRead(S1)) {delay(1);}
    digitalWrite(LED_BUILTIN,LOW);
  }
}

void setupPins() {
  //set the pin states
  pinMode(C1, INPUT_PULLUP);
  pinMode(C10, INPUT_PULLUP);
  pinMode(C25, INPUT_PULLUP);
  pinMode(S1, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}
