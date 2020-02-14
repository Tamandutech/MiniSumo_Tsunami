#include <analogWrite.h>
/*#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu(Wire);*/

  #define sharpF 12
  #define sharpE 13
  #define sharpD 13
  
  
  #define pwmB 23
  #define b1 5
  #define b2 1
  #define stby 3
  #define a1 26
  #define a2 19
  #define pwmA 18
  //sensor de linha
  #define linha1 2
  #define linha2 4
  //acelerometro
  float yInicial = 0;
  //potencia
  int a = 100;
  int b = 100;
  bool direc = true;
  
void setup() {
  pinMode(pwmB, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(linha1, INPUT);
  pinMode(linha2, INPUT);
  pinMode(sharpF, INPUT);
  pinMode(sharpE, INPUT);
  pinMode(sharpD, INPUT);
  digitalWrite(stby,1);
  Serial.begin(9600);
}
 float media = 0;
 float cont = 0;
 int i = 0;

 int media10(int i){
    int media=0;
    for(int a=0;a<1000;a++){
        media+=analogRead(i);
      }
    return media/1000;
  
  }
 
void loop() {
  Serial.print(media10(13));
  Serial.print(" ");
  Serial.print(media10(12));
  Serial.print(" ");
  Serial.println(media10(14));
  delay(500);
}
