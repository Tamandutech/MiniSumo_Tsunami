#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>
#include <analogWrite.h>

const byte sharpF = 12;
const byte sharpT = 13;
const byte medianFilterWindowSize = 5;
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
  String var;
  int cont = 0;
  String est;

  
void setup() {
  Serial.begin(115200);
  Dabble.begin("MyEsp32");

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
  
  delay(4800);  

  //Valores iniciais do sensor
  //yInicial = mpu.getAngleY();
  
}

void loop() {
  while(var != "9"){
    Dabble.processInput();            
    if (Terminal.available() != 0)
    {
      while (Terminal.available() != 0)
      {
        var = Terminal.read();
        if(var != "9"){
          est = var;
          }
      }
      Serial.println(var);
    }
}

   escolheEstrategia();

    //mpu.update();
  unsigned int sharp1 = analogRead(12);
  unsigned int sharp2 = analogRead(13);
  valorSensor1 = analogRead(linha1);
  valorSensor2 = analogRead(linha2);
  //float yAtual = mpu.getAngleY();
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
}
