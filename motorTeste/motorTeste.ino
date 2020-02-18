#include <analogWrite.h>
#define pwmB 23
#define b1 5
#define b2 1
#define stby 3
#define a1 26
#define a2 19
#define pwmA 18
  
void setup() {
  pinMode(pwmB, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  digitalWrite(stby,1);
}

void loop() {
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, 100);
  analogWrite(pwmA, 100);
  delay(10000);
  analogWrite(pwmB, 0);
  analogWrite(pwmA, 0);
  delay(1000);
}
