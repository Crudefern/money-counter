#include <Arduino.h>
#include <EEPROM.h>
// #include <SoftwareSerial.h>
#include "functions.hpp"
// #define EE_TEST_VAL 0x315A
#include "EEvar.h"
//setup values (change pin numbers in src/functions.cpp)
const int timeout = 1000; // time in between the last button press and eeprom write
#define initialWantMoney 242.98 // set this to the target amout of money you want
// A tinytesla with spare IGBTs and the discount code ELECTROBOOM10 costs $242.98
// An oculus quest 2 256GB with the standard strap is $429.99

// SoftwareSerial mySerial(-1, 4); // RX, TX (TX is XTAL2/TP2)

const EEstore<float> eeMoney(0);
const EEstore<float> eeWantMoney(initialWantMoney);

void eepromClear() { //this has to be put here because of the eevar library
  money = 0;
  eeMoney << money;
  multiBlink(500,3);
}

void setup() {
  // mySerial.begin(9600); //for debugging
  setupPins(); //set the pin states
  delay(50);
  if (!digitalRead(C1) && !digitalRead(C10) && !digitalRead(C25) && !digitalRead(S1)) {eepromClear();}
  if (!digitalRead(C25) && !digitalRead(S1)) {readButtons(wantMoney);}
  eeMoney >> money; // get money count from eeprom
  oldMoney = money;
  ledBlink(15);
}


void loop() {
  float tempMoney = 0;
  time = millis();
  readButtons(money);

  // write to the EEPROM 
  if (money != oldMoney && time - oldTime >= timeout) {
    // mySerial.println("WRITING");
    oldMoney = money;
    oldTime = time;
    eeMoney << money; // write money count to eeprom
    multiBlink(100,3);
  }

  // blink when you have enough money
  if (money >= wantMoney) {while (true) {multiBlink(30,32767);}}
  if (money < 0) {money = 0;}
  // mySerial.println(money); //debugging
  // mySerial.println(oldMoney); //debugging
}


