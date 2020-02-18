//Y >tras <frente
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

float inicialY;
float atualY = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  mpu6050.update();
  inicialY = mpu6050.getAngleY();
  Serial.println(inicialY);
}

int tras=0,frent=0;
void loop() {
  mpu6050.update();
  float atualY = mpu6050.getAngleY();
  float atualX = mpu6050.getAngleX();
  Serial.print(atualY);
  if(atualY > inicialY+4){
    //Serial.println("Traseira levantada+++++++++++");
    tras++;
  }else if(atualY < inicialY-4){
    //Serial.println("Frente levantada-------------");
    frent++;
  }else{
    //Serial.println("Normal");
    tras=0;
    frent=0;
  }
  if(tras>10){
    Serial.println("Traseira levantada+++++++++++");
    tras=0;
    frent=0;
  }
  else if(frent>10){
    Serial.println("Frente levantada-------------");
    tras=0;
    frent=0;
  }
  else Serial.println("");
}
