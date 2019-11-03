
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

void loop() {

  
  mpu.update();
  float yAtual = mpu.getAngleY();
  if(yAtual < (yInicial - 1)){
    Serial.println("Levantado");
    }else{Serial.println("Ta no chão");}
  
 /* //Serial.print("angleX : ");
  //Serial.println(mpu.getAngleX());
  Serial.print("\tangleY : ");
  Serial.println(mpu.getAngleY());
  //Serial.print("\tangleZ : ");
  //Serial.println(mpu.getAngleZ());
  */

  
}
