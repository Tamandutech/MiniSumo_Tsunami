//Y >tras <frente
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <LinkedList.h>
#include <Gaussian.h>
#include <GaussianAverage.h>

MPU6050 mpu6050(Wire);

GaussianAverage angleY(10);

float inicialY;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  inicialY = 4.10;
}

void loop() {
  mpu6050.update(); //atualiza mpu
  angleY += mpu6050.getAngleY();
  angleY.process();
  Serial.print(angleY.mean);
  if(angleY.mean>inicialY+3) Serial.print(" - TRAAAAAAAAAAS   ");
  else if(angleY.mean<inicialY-3) Serial.print(" - FRENTEEEEEEEE   ");
  Serial.println();
}
