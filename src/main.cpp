#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "functions.hpp"
#define EE_TEST_VAL 0x315A    // library default is 0x3159
#include "EEvar.h"
//setup values (change pin numbers in src/functions.cpp)
const int timeout = 5000; // time before writing to the eeprom
const float wantMoney = 242.98; // set this to the target amout of money you want
// A tinytesla with spare IGBTs and the discount code ELECTROBOOM10 costs $242.98
// An oculus quest 2 256GB with the standard strap is $429.99

SoftwareSerial mySerial(-1, 4); // RX, TX (TX is XTAL2/TP2)

const EEstore<float> eeMoney(0);

void setup() {
  mySerial.begin(9600); //for debugging
  setupPins(); //set the pin states
  // setup money count from eeprom
  delay(50);
  if (!digitalRead(C1) && !digitalRead(C10) && !digitalRead(C25) && !digitalRead(S1)) {eepromClear();}
  eeMoney >> money;
  // money = 0;
  oldMoney = money;
}


void loop() {
  time = millis();
  readButtons();
  // write to the EEPROM 
  if (money != oldMoney && time - oldTime >= timeout) {
    oldMoney = money;
    oldTime = time;
    // eeMoney << money;
    ledBlink(1000);
  }
  // blink when you have enough money
  if (money >= wantMoney) {while (true) {multiBlink(30,32767);}}
  if (money < 0) {money = 0;}
  mySerial.println(money); //debugging
}