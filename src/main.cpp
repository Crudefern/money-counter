#include <Arduino.h>
#include "functions.hpp"
// #define EE_TEST_VAL 0x315A // uncomment when changing the hardcoded wantmoney
#include "EEvar.h"
// setup values (change pin numbers in src/functions.cpp)
const int timeout = 1000; // time in between the last button press and eeprom write
#define initialWantMoney 49.99f // set this to the target amout of money you want
// A tinytesla with spare IGBTs and the discount code ELECTROBOOM10 costs $242.98
// An oculus quest 2 256GB with the standard strap is $499.99
// KSP2 will cost $49.99 

const EEstore<float> eeMoney(0);
const EEstore<float> eeWantMoney(initialWantMoney);

void eepromClear() { // this has to be put here because of the eevar library
  money = 0;
  eeMoney << money;
  multiBlink(500, 3);
}

void setup() {
  setupPins(); // set the pin states
  delay(50);
  if (!digitalRead(C1) && !digitalRead(C10) && !digitalRead(C25) && !digitalRead(S1))  {eepromClear();} // clear the eeprom
  if (digitalRead(C1) && digitalRead(C10) && !digitalRead(C25) && !digitalRead(S1)) {
    while (true) {
      wantMoney = 0;
      wantMoney += readButtons(); // this line and the line below set and save wantMoney
      if (!digitalRead(C1) && !digitalRead(C10) && !digitalRead(C25) && !digitalRead(S1)) {
        eeWantMoney << wantMoney;
        while (true) {
          delay(1);
        }
      }
    }
  }
  eeMoney >> money; // get money count from eeprom
  eeWantMoney >> wantMoney;
  oldMoney = money;
  ledBlink(15);
}

void loop() {
  time = millis();
  money += readButtons(); // get button states

  // write to the EEPROM
  if (money - oldMoney > 0.001 && time - oldTime >= timeout) {
    oldMoney = money;
    oldTime = time;
    eeMoney << money; // write money count to eeprom
    multiBlink(100, 3);
  }

  // blink when you have enough money
  if (money >= wantMoney) {
    while (true) {multiBlink(30, 32767);}
  }
  if (money < 0) {money = 0;} // a failsafe
}