#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "functions.hpp"
//setup values
const int timeout = 5000; //time before writing to the eeprom
const float wantMoney = 242.98; //set this to the target amout of money you want
// A tinytesla with spare IGBTs and the discount code ELECTROBOOM10 costs $242.98
// An oculus quest 2 256GB with the standard strap is $429.99

SoftwareSerial mySerial(-1, 10); // RX, TX

void setup() {
  mySerial.begin(9600); //for debugging
  //set the pin states
  pinMode(C1, INPUT_PULLUP);
  pinMode(C10, INPUT_PULLUP);
  pinMode(C25, INPUT_PULLUP);
  pinMode(S1, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  //setup money count from eeprom
  if (digitalRead(C1) && digitalRead(C10) && digitalRead(C25) && digitalRead(S1)) {eepromClear();}
  EEPROM.get(addr, money);
  oldMoney = money;
}
//helpers
void ledblink(int blinkTime) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkTime);
  digitalWrite(LED_BUILTIN, LOW);
}

void eepromClear() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

void loop() {
  time = millis();

  //write to the EEPROM
  if (money != oldMoney && time - oldTime >= timeout) {
    oldMoney = money;
    oldTime = time;
    EEPROM.put(addr, money);
    ledblink(1000);
  }
  //blink when you have enough money
  if (money >= wantMoney) {while (true) {ledblink(50); delay(100);}}
//  mySerial.println(money); //debugging
}