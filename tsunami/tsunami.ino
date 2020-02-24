#include <BluetoothSerial.h>
#include <LinkedList.h>
#include <Gaussian.h>
#include <GaussianAverage.h>
#include <analogWrite.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char BT = 'Z';
int tempo = 4900;
char estrategia = 'a';
char lupi = 'H';

MPU6050 mpu(Wire);
  #define sharpF 12
  #define sharpE 13
  #define sharpD 14

  #define pwmB 18
  #define b1 26
  #define b2 19
  #define stby 3
  #define a1 5
  #define a2 1
  #define pwmA 23
  //sensor de linha
  #define linha1 2
  #define linha2 4
  //acelerometro
  //float yInicial = 0;
  //potencia
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
  SerialBT.begin("Tsunami"); //Bluetooth device name
  //Serial.begin(9600);
  //Wire.begin();
  //mpu.begin();
  //mpu.calcGyroOffsets(true);
  SerialBT.println("LIGOUUUU");
  while(BT != '0'){
      if(SerialBT.available()) {
          BT = SerialBT.read();
          Serial.print(BT);
      }
      if(BT == '+'){
          tempo += 100;
      }else if(BT == '-'){
          tempo -= 100;  
      }else if(BT == 'C'){
          SerialBT.println("Check");
          SerialBT.print("Modo: ");
          SerialBT.println(estrategia);
          SerialBT.print("Delay: ");
          SerialBT.println(tempo);  
      }else if(BT == '0') {
        break;
      }else {
          if(!(BT == 13 || BT == 10)){
              estrategia = BT;
          }
      }
  }
  delay(tempo);
  SerialBT.println("Start");
  SerialBT.println(estrategia);
  //mpu.update();
  //Valores iniciais do sensor
  //yInicial = mpu.getAngleY();

  switch (estrategia){
    case 'a': //frentao
      move('D','F',255);
      move('E','F',255);
      SerialBT.print("FRENTAAO");
      delay(500);
      
    break;

    case 'b':  //curvao
      if(direc){
        move('D','T',255);
        move('E','F',255);
        delay(30);
        move('D','F',255);
        move('E','F',200);
        delay(2000);
      }
      else{
        move('E','T',255);
        move('D','F',255);
        delay(30);
        move('E','F',255);
        move('D','F',200);
        delay(2000);
      }
    break;

     default:
      move('D','F',255);
      move('E','F',255);
      delay(1000);
      SerialBT.print("DEFAAAAAAULT");
      break;

    //case 'c':  //babacas

    //case 'd':  //costas

    //case 'e':  //costas curvao
  }
  SerialBT.print("PARAAAAAAAAAAAA");
}
 
void loop() {

  switch(lupi){
    //case 'F': //parado até leitura
      
    //case 'G': //girando
      
    case 'H': //suicide
      while (linha1>500 && linha2>500){ 
        while(sharpE<50 && sharpD<50){  //não ta dos lados
          move('D','F',255);
          move('E','F',255);
          SerialBT.println("loop");
        }
        if(sharpE>=50){
          move('D','F',255);
          move('E','T',255);
          delay(100);
        }
        else{
          move('D','T',255);
          move('E','F',255);
          delay(100);
        }
      }
      //se ler a linha
      move('D','T',255);
      move('E','T',255);
      delay(50);
      if(direc){
        move('D','T',255);
        move('E','T',255);
        delay(100);
      }
      else{
        move('E','T',255);
        move('D','T',255);
        delay(100);
      }
      break;
      default:
      SerialBT.println("DEFaaUUUuuLLllti");
  }
 

}

void move(char M, char S, int V) {
  /*
    M = qual motor 
    'D' -> motor direito || 'E' -> motor esquerdo
    S = quak sentido de rotação
    'F' -> frente || 'T' -> tras
    V = velocidade de rotação
    0 ~ 255
  */

  if ((M == 'D') and (S == 'T')) {
    digitalWrite(a1,1);
    digitalWrite(a2,0);
    analogWrite(pwmA,V);
  }else if ((M == 'D') and (S == 'F')) {
    digitalWrite(a1,0);
    digitalWrite(a2,1);
    analogWrite(pwmA,V);
  }else if ((M == 'E') and (S == 'F')) {
    digitalWrite(b1,0);
    digitalWrite(b2,1);
    analogWrite(pwmB,V);
  }else if ((M == 'E') and (S == 'T')) {
    digitalWrite(b1,1);
    digitalWrite(b2,0);
    analogWrite(pwmB,V);
  }
}
