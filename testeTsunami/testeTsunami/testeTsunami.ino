#include <analogWrite.h>
//#include <MPU6050_tockn.h>
//#include <Wire.h>
#include <SharpDistSensor.h>


//MPU6050 mpu(Wire);

const byte sharpF = 12;
const byte sharpT = 13;
const byte medianFilterWindowSize = 5;
SharpDistSensor if1(sharpF, medianFilterWindowSize);
SharpDistSensor if2(sharpT, medianFilterWindowSize);

  #define sharpF 12
  #define sharpT 13
  #define pwmB 23
  #define b1 5
  #define b2 1
  #define stby 3
  #define a1 26
  #define a2 19
  #define pwmA 18
  //sensor de linha
  #define linha1 4
  #define linha2 2
  //sharp
  int valorSensor1 = 0;
  int valorSensor2 = 0;

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
  pinMode(sharpT, INPUT);
  digitalWrite(stby,1);
  Serial.begin(9600);
  delay(1000);  
  
  
  
}
 
void loop() {
  
  unsigned int sharp1 = if1.getDist();
  unsigned int sharp2 = if2.getDist();
  valorSensor1 = analogRead(linha1);
  valorSensor2 = analogRead(linha2);
  /*if(analogRead(12) > 500 || analogRead(13) > 500){
  frente();
    }else {direita();}*/
  //sharp < 800
  //Linha < 3000
  direita();
  Serial.print("Linha1: ");
  Serial.println(valorSensor1);
  Serial.print("Linha2: ");
  Serial.println(valorSensor1);
  
  /*if(sharp1 < 150 || sharp2 < 150){
    if(sharp1 > sharp2){
      frente();
      }
      else{
        tras();
        }
    }*/

  /*if(valorSensor1 > 500 || valorSensor2 > 500){
   fugaLinha();
   }*/
}

void frente(){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, 100);
  analogWrite(pwmA, 100);
}
void tras(){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, 100);
  analogWrite(pwmA, 100);
}
void direita(){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, 60);
  analogWrite(pwmA, 60);
  }
 void esquerda(){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, 100);
  analogWrite(pwmA, 100);
  }
void fugaLinha(){
  if(valorSensor1 > valorSensor2){
      direita();
      delay(500);
      frente();
      delay(500);
    }
    else{
      tras();
      delay(500);
      esquerda();
      delay(500);
     }
  }
