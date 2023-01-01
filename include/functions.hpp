#include <Arduino.h>

//button pins
extern const int C1=10; //adds 1 cent
extern const int C10=9; //adds 10 cents
extern const int C25=8; //adds 25 cents
extern const int S1=7;  //adds 1 dollar

extern const int addr = 0;
extern float money; 
extern float oldMoney;
extern unsigned long time = millis();
extern unsigned long oldTime = time;
extern bool add = 1;

void readButtons();
void ledBlink(int blinkTime);