#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "functions.hpp"
#include "EEvar.h"
//setup values (change pin numbers in src/functions.cpp)
const int timeout = 2000; // time before writing to the eeprom
const float wantMoney = 242.98; // set this to the target amout of money you want
// A tinytesla with spare IGBTs and the discount code ELECTROBOOM10 costs $242.98
// An oculus quest 2 256GB with the standard strap is $429.99

SoftwareSerial mySerial(-1, 4); // RX, TX (TX is XTAL2/TP2)

const EEstore<float> eeMoney(0);

void setup() {
  mySerial.begin(9600); //for debugging
  setupPins(); //set the pin states
  delay(50);
  if (!digitalRead(C1) && !digitalRead(C10) && !digitalRead(C25) && !digitalRead(S1)) {eepromClear();}
  eeMoney >> money; // get money count from eeprom
  oldMoney = money;
}


void loop() {
  time = millis();
  readButtons();
  // write to the EEPROM 
  if (money != oldMoney && time - oldTime >= timeout) {
    mySerial.println("WRITING");
    oldMoney = money;
    oldTime = time;
    eeMoney << money; // write money count to eeprom
    multiBlink(100,3);
  }
  // blink when you have enough money
  if (money >= wantMoney) {while (true) {multiBlink(30,32767);}}
  if (money < 0) {money = 0;}
  mySerial.println(money); //debugging
  mySerial.println(oldMoney); //debugging
}


void eepromClear() { //this has to be put here because of the eevar library
  money = 0;
  eeMoney << money;
  multiBlink(500,5);
}