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

char BT = 1231242;
int tempo = 4900;
int modo = 1;

MPU6050 mpu(Wire);
  #define sharpF 12
  #define sharpE 13
  #define sharpD 14

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
  SerialBT.begin("Tsunami"); //Bluetooth device name
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);
  SerialBT.println("LIGOUUUU");
  while(BT != 0){
      if(SerialBT.available()) {
          BT = SerialBT.read();
          Serial.print(BT);
      }
      while(BT == 1234){
          if(SerialBT.available()) tempo = SerialBT.read();
          BT = modo;
          SerialBT.println("Delay");
      }if(BT != 1234){
          modo = BT;  
      }else if(BT == 4321){
          SerialBT.println("Check");
          SerialBT.print("Modo: ");
          SerialBT.println(modo);
          SerialBT.print("Delay: ");
          SerialBT.println(tempo);  
      }
  }
  delay(tempo);
  SerialBT.println("Start");
  mpu.update();
  //Valores iniciais do sensor
  yInicial = mpu.getAngleY();
}
 
void loop() {

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
void fugaAdversario(){
  tras(200, 100);
  delay(250);
  Serial.println("Entrou aqui irmão");
  }
