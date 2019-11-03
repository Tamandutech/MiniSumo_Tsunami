
#include <SharpDistSensor.h>

// Analog pin to which the sensor is connected
const byte sensorPin = 12;

// Window size of the median filter (odd number, 1 = no filtering)
const byte medianFilterWindowSize = 5;

// Create an object instance of the SharpDistSensor class
SharpDistSensor sensor(sensorPin, medianFilterWindowSize);


void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}
  
void loop() {
  // Get distance from sensor
  unsigned int distance = sensor.getDist();
  // Print distance to Serial
  Serial.println(distance);
  // Wait some time
  delay(50);
}
