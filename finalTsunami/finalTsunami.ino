#include <analogWrite.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SharpDistSensor.h>
MPU6050 mpu(Wire);
const byte sharpF = 12;
const byte sharpT = 13;
const byte medianFilterWindowSize = 5;
SharpDistSensor if1(sharpF, medianFilterWindowSize);
SharpDistSensor if2(sharpT, medianFilterWindowSize);

  //#define sharpF 12
  //#define sharpT 13

  #define dip1 33
  #define dip2 32
  #define dip3 35
  #define dip4 34

  #define button 36
  
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
  //sharp
  int valorSensor1 = 0;
  int valorSensor2 = 0;
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
  pinMode(sharpT, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(dip1,INPUT);
  pinMode(dip2,INPUT);
  pinMode(dip3,INPUT);
  pinMode(dip4,INPUT);
  digitalWrite(stby,1);
  //Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);
  while(digitalRead(button)==1){}
  if(digitalRead(dip1)==1){
    direc=1; //esquerda
  }else{
    direc=0; //direita
  }
  delay(4900);  
  mpu.update();
  //Valores iniciais do sensor
  yInicial = mpu.getAngleY();
  if(digitalRead(dip2)==1){
    frente(200,255);
    delay(500);
  }
  if(digitalRead(dip3)==1){
    drift();  
  }
}
 
void loop() {
  mpu.update();
  unsigned int sharp1 = if1.getDist();
  unsigned int sharp2 = if2.getDist();
  valorSensor1 = analogRead(linha1);
  valorSensor2 = analogRead(linha2);
  float yAtual = mpu.getAngleY();
  
 /*Serial.println(yInicial);
 if(yAtual < (yInicial - 1.5) ){
    direita(150, 80);
    delay(80);
    tras(200, 200);
    delay(100);
 }
 */ 
//segue adversário
  if(sharp1 < 800 || sharp2 < 800){
    frente(150, 150);
    if(sharp1 < sharp2){
      frente(220, 200);
    }else{
      frente(200, 220);
    }
  }else if(direc==1){
    esquerda(a, b);
  }else{
    direita(a,b);  
  }

  if(valorSensor2 < 1000 || valorSensor2 < 1000){
   fugaLinha();
  }
  
  /*Giroscopio: utilizar angulo y(rampado ou não) e z(pegou de lado)
  Serial.print("angleX : ");
  Serial.print(mpu.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu.getAngleZ());
  
  //Acelerometro: accY e accX variando de -0.2 a -0.5 quando parado
  xAccInicial = mpu.getAccX(); 
  yAccInicial = mpu.getAccY();
  Serial.print("x atual: ");
  Serial.println(xAccInicial);
  Serial.print("y atual");
  Serial.println(yAccInicial);
  */
}




void tras(int pa, int pb){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
}
void frente(int pa, int pb){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
}
void esquerda(int pa, int pb){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
  }
 void direita(int pa, int pb){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
  }

  
void fugaLinha(){
  if(valorSensor1 > valorSensor2){
      tras(250, 250);
      delay(500);
      esquerda(a, b);
      delay(500);
    }
    else{
      tras(250, 250);
      delay(500);
      direita(a, b);
      delay(500);
     }
}

void drift(){
  if(direc==1){
    esquerda(250,250);
    delay(120);
    frente(250, 110);
    delay(1000);
  }
  else{
    direita(250,250);
    delay(120);
    frente(120, 250);
    delay(1000);
  }
  direc = !direc;
}
