#include <analogWrite.h>
//#include <MPU6050_tockn.h>
//#include <Wire.h>
//#include <SharpDistSensor.h>
//MPU6050 mpu(Wire);
const byte sharpF = 12;
const byte sharpT = 13;
const byte medianFilterWindowSize = 5;
//SharpDistSensor if1(sharpF, medianFilterWindowSize);
//SharpDistSensor if2(sharpT, medianFilterWindowSize);
  //#define sharpF 12
  //#define sharpT 13
  #define stby 3
  #define dip1 33
  #define dip2 32
  #define dip3 35
  #define dip4 34
  #define button 36
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
  init_motores();
  pinMode(stby, OUTPUT);
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
  //Wire.begin();
  //mpu.begin();
  //mpu.calcGyroOffsets(true);
  
  while(digitalRead(button)==1){}
  if(digitalRead(dip1)==1){
    direc=1; //esquerda
  }else{
    direc=0; //sireita
  }
  delay(4800);  
  //mpu.update();
  //Valores iniciais do sensor
  //yInicial = mpu.getAngleY();
  if(digitalRead(dip2)==1){
    frente(200,255);
    delay(500);
  }
  if(digitalRead(dip3)==1){
    drift();  
  }
}
 
void loop() {
  //mpu.update();
  unsigned int sharp1 = analogRead(12);
  unsigned int sharp2 = analogRead(13);
  valorSensor1 = analogRead(linha1);
  valorSensor2 = analogRead(linha2);
  //float yAtual = mpu.getAngleY();
  
 /*if(abs(yInicial - yAtual) > 3){
  Serial.println("Entrou");
   fugaAdversario();
 }*/
 
//segue adversário
//rever, provavelmente vai bugar
  if(sharp1 > 100 || sharp2 > 100){
    frente(255, 255);
    if(sharp1 < sharp2){
      frente(255, 180);
    }else{  
      frente(180, 255);
    }
  }else if(direc==1){
    esquerda(a, b);
  }else{
    direita(a,b);  
  }

  if(valorSensor2 < 1000 || valorSensor1 < 1000){
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




  
