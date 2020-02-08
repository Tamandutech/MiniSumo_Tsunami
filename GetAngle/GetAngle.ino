
#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu(Wire);
float yInicial = 0;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);
  mpu.update(); 
  yInicial = mpu.getAngleY();
}
 float mediaV = 0;
 float contV = 0;
 float media = 0;
 float cont = 0;
 int i = 0;
void loop() {

  
  mpu.update();
  float yAtual = mpu.getAngleY();
 if(abs(yInicial - yAtual) > 3){
  Serial.println("levantado");
  }else{Serial.println("não");}
 //Serial.print("\tangleY : ");
 //Serial.println(mpu.getAngleY());

  
}
